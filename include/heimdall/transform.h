#pragma once

#include "heimdall/common.h"
#include "heimdall/matrix.h"
#include "heimdall/geometry.h"
#include "heimdall/quaternion.h"

HEIMDALL_NAMESPACE_BEGIN

/**
 * \brief Transformation class containing matrix representations
 */

class Transform {
  public:
  	/// Transfor public methods
  	Transform();
  	Transform(const float mat[4][4]);
  	Transform(const Matrix& _m);
  	Transform(const Matrix& _m, const Matrix& _mInv);

  	bool isIdentity() const;
  	bool SwapsHandedness() const;

  	bool operator==(const Transform& t) const;
  	bool operator!=(const Transform& t) const;

  	Transform operator*(const Transform& t) const;

  	friend Transform Inverse(const Transform& t);
  	friend Transform Transpose(const Transform& t);

  	template <typename T>
    inline Point3<T> operator()(const Point3<T>& p) const;

    template <typename T>
    inline Vec3<T> operator()(const Vec3<T>& v) const;

    template <typename T>
    inline Normal3<T> operator()(const Normal3<T>& n) const;

    inline Ray operator()(const Ray& r) const;

    inline RayDifferential operator()(const RayDifferential& r) const;

    inline Bounds3f operator()(const Bounds3f& b) const;

  private:
  	/// Transform private data
  	Matrix m, mInv;
  	friend class Quaternion;
    friend class AnimatedTransform;
};

Transform Translate(const Vec3f& delta);
Transform Scale(float x, float y, float z);
Transform RotateX(float theta);
Transform RotateY(float theta);
Transform RotateZ(float theta);
Transform Rotate(float theta, const Vec3f& axis);
Transform LookAt(const Point3f& pos, const Point3f& look, const Vec3f& up);

/**
 * \breif Animated Transform 
 */

class AnimatedTransform {
  public:
    /// AnimatedTransform public methods
    AnimatedTransform(const Transform* startTransform, float startTime,
                      const Transform* endTransform,   float endTime);

    void Decompose(const Matrix& mSRT, Vec3f* T, Quaternion* R, Matrix* S);
    void Interpolate(float time, Transform* t) const;

    Ray operator()(const Ray& r) const;
    RayDifferential operator()(const RayDifferential& r) const;
    Point3f operator()(float time, const Point3f& p) const;
    Vec3f operator()(float time, const Vec3f &v) const;


  private:
    /// AnimatedTransform private data
    const Transform* startTransform;
    const Transform* endTransform;
    const float startTime, endTime;
    const bool actuallyAnimated;
    Vec3f T[2];
    Quaternion R[2];
    Matrix S[2];
    bool hasRotation;
};

/**
 * \breif Transformation template methods
 */

template <typename T>
inline Point3<T> Transform::operator()(const Point3<T>& p) const {
	T x = p.x, y = p.y, z = p.z;
    T xp = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z + m.m[0][3];
    T yp = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z + m.m[1][3];
    T zp = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z + m.m[2][3];
    T wp = m.m[3][0] * x + m.m[3][1] * y + m.m[3][2] * z + m.m[3][3];

    if (wp == 1) {
        return Point3<T>(xp, yp, zp);
    }
    return Point3<T>(xp, yp, zp) / wp;
}

template <typename T>
inline Vec3<T> Transform::operator()(const Vec3<T>& v) const {
	T x = v.x, y = v.y, z = v.z;
	return Vec3<T>(m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z,
                   m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z,
                   m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z);
}

template <typename T>
inline Normal3<T> Transform::operator()(const Normal3<T>& n) const {
    T x = n.x, y = n.y, z = n.z;
    return Normal3<T>(mInv.m[0][0] * x + mInv.m[1][0] * y + mInv.m[2][0] * z,
                      mInv.m[0][1] * x + mInv.m[1][1] * y + mInv.m[2][1] * z,
                      mInv.m[0][2] * x + mInv.m[1][2] * y + mInv.m[2][2] * z);
}

inline Ray Transform::operator()(const Ray& r) const {
	Point3f o = (*this)(r.o);
	Vec3f d = (*this)(r.d);
	return Ray(o, d, r.tMax, r.time, r.medium);
}

inline RayDifferential Transform::operator()(const RayDifferential& r) const {
	Ray tr = (*this)(Ray(r));
    RayDifferential ret(tr.o, tr.d, tr.tMax, tr.time, tr.medium);
    ret.hasDifferentials = r.hasDifferentials;
    ret.rxOrigin = (*this)(r.rxOrigin);
    ret.ryOrigin = (*this)(r.ryOrigin);
    ret.rxDirection = (*this)(r.rxDirection);
    ret.ryDirection = (*this)(r.ryDirection);
    return ret;
}

/// Method by Jim Arvo in Graphics Gems (1990)
inline Bounds3f Transform::operator()(const Bounds3f& a) const {
	float aTemp, bTemp;
    float aMin[3], aMax[3];
    float bMin[3], bMax[3];

    /*Copy box A into a min array and a max array for easy reference.*/

    aMin[0] = a.pMin.x;  
    aMin[1] = a.pMin.y;  
    aMin[2] = a.pMin.z;  

    aMax[0] = a.pMax.x;
	aMax[1] = a.pMax.y;
	aMax[2] = a.pMax.z;

    /* Take care of translation by begining at T */

    bMin[0] = bMax[0] = m.m[0][3];
    bMin[1] = bMax[1] = m.m[1][3];
    bMin[2] = bMax[2] = m.m[2][3];

    /* Now find the extreme points by considering the product of the */
    /* min and max with each component of M.  */
                     
    for(int i = 0; i < 3; ++i) {
	    for(int j = 0; j < 3; ++j) {
	        aTemp = m.m[i][j] * aMin[j];
	        bTemp = m.m[i][j] * aMax[j];
	        if (aTemp < bTemp) { 
	            bMin[i] += aTemp; 
	            bMax[i] += bTemp;
	        } else { 
	            bMin[i] += bTemp; 
	            bMax[i] += aTemp;
	        }
	    }
    }

    /* Copy the result into the new box. */
	return Bounds3f(Point3f(bMin[0], bMin[1], bMin[2]),
				    Point3f(bMax[0], bMax[1], bMax[2]));
}

HEIMDALL_NAMESPACE_END