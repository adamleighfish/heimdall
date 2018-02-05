#pragma once

#include "heimdall/common.h"
#include "heimdall/matrix.h"
#include "heimdall/geometry.h"

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

  	bool operator==(const Transform& t) const;
  	bool operator!=(const Transform& t) const;

  	Transform operator*(const Transform& t) const;

  	friend Transform Inverse(const Transform& t);
  	friend Transform Transpose(const Transform& t);

  	template <typename T>
    Point3<T> operator()(const Point3<T>& p) const;

    template <typename T>
    Vec3<T> operator()(const Vec3<T>& v) const;

    template <typename T>
    Normal3<T> operator()(const Normal3<T>& n) const;

    Ray operator()(const Ray& r) const;

    RayDifferential operator()(const RayDifferential& r) const;

    Bounds3f operator()(const Bounds3f& b) const;

  private:
  	/// Transform private data
  	Matrix m, mInv;
  	friend class Quaternion;
};

Transform Translate(const Vec3f& delta);
Transform Scale(float x, float y, float z);
Transform RotateX(float theta);
Transform RotateY(float theta);
Transform RotateZ(float theta);
Transform Rotate(float theta, const Vec3f& axis);
Transform LookAt(const Point3f& pos, const Point3f& look, const Vec3f& up);

/**
 * \breif Transformation template methods
 */

template <typename T>
Point3<T> Transform::operator()(const Point3<T>& p) const {
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
Vec3<T> Transform::operator()(const Vec3<T>& v) const {
	T x = v.x, y = v.y, z = v.z;
	return Vec3<T>(m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z,
                   m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z,
                   m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z);
}

template <typename T>
Normal3<T> Transform::operator()(const Normal3<T>& n) const {
    T x = n.x, y = n.y, z = n.z;
    return Normal3<T>(mInv.m[0][0] * x + mInv.m[1][0] * y + mInv.m[2][0] * z,
                      mInv.m[0][1] * x + mInv.m[1][1] * y + mInv.m[2][1] * z,
                      mInv.m[0][2] * x + mInv.m[1][2] * y + mInv.m[2][2] * z);
}

HEIMDALL_NAMESPACE_END