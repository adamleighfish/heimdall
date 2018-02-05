#pragma once

#include "heimdall/common.h"

HEIMDALL_NAMESPACE_BEGIN

/* ===================================================================
    This file contains a few templates and specializations, which
    provide 2/3D points, vectors, and normals over different
    underlying data types. Points, vectors, and normals are distinct
    because they transform differently under homogeneous coordinate 
    transformations.
 * =================================================================== */

/**
 * \brief Generic 2-dimensional vector data structure
 */

template <typename T>
class Vec2 {
  public:
    /// Vec2 public data
    T x, y;

    /// Vec2 public methods
    Vec2() { 
        x = y = 0; 
    }

    Vec2(T _x, T _y) {
        x = _x;
        y = _y;
    }

    Vec2<T>& operator=(const Vec2<T>& v) {
        x = v.x;
        y = v.y;
        return *this;
    }

    T& operator[](int i) {
        if (i == 0) return x;
        return y;
    }

    Vec2<T> operator+(const Vec2<T>& v) const { 
        return Vec2<T>(x + v.x, y + v.y); 
    }

    Vec2<T>& operator+=(const Vec2<T>& v) {
        x += v.x; 
        y += v.y;
        return *this;
    }

    Vec2<T> operator-(const Vec2<T>& v) const { 
        return Vec2<T>(x - v.x, y - v.y); 
    }

    Vec2<T>& operator-=(const Vec2<T>& v) {
        x -= v.x; 
        y -= v.y;
        return *this;
    }

    template <typename U>
    Vec2<T> operator*(U s) const {
        return Vec2<T>(x * s, y * s);
    }

    template <typename U>
    Vec2<T>& operator*=(U s) {
        x *= s;
        y *= s;
        return *this;
    }

    template <typename U>
    Vec2<T> operator/(U s) const {
        double inv = 1.0 / double(s);
        return Vec2<T>(x * inv, y * inv);
    }

    template <typename U>
    Vec2<T> operator/=(U s) {
        double inv = 1.0 / double(s);
        x *= inv;
        y *= inv;
        return *this;
    }

    bool operator==(const Vec2<T>& v) const { 
        return (x == v.x) and (y == v.y); 
    }

    bool operator!=(const Vec2<T>& v) const { 
        return (x != v.x) or (y != v.y); 
    }

    Vec2<T> operator-() const { 
        return Vec2<T>(-x, -y); 
    }

    float LengthSquared() { 
        return x * x + y * y; 
    }

    float Length() { 
        return std::sqrt(LengthSquared()); 
    }
};

/**
 * \brief Generic 3-dimensional vector data structure
 */

template <typename T>
class Vec3 {
  public:
    /// Vec3 public data
    T x, y, z;

    /// Vec3 public methods
    Vec3() { 
        x = y = z = 0; 
    }

    Vec3(T _x, T _y, T _z) {
        x = _x;
        y = _y;
        z = _z;
    }

    Vec3<T>& operator=(const Vec3<T>& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    T& operator[](int i) {
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }

    Vec3<T> operator+(const Vec3<T>& v) const { 
        return Vec3<T>(x + v.x, y + v.y, z + v.z); 
    }

    Vec3<T>& operator+=(const Vec3<T>& v) {
        x += v.x; 
        y += v.y; 
        z += v.z;
        return *this;
    }

    Vec3<T> operator-(const Vec3<T>& v) const { 
        return Vec3<T>(x - v.x, y - v.y, z - v.z); 
    }

    Vec3<T>& operator-=(const Vec3<T>& v) {
        x -= v.x; 
        y -= v.y; 
        z -= v.z;
        return *this;
    }

    template <typename U>
    Vec3<T> operator*(U s) const {
        return Vec3<T>(x * s, y * s, z * s);
    }

    template <typename U>
    Vec3<T>& operator*=(U s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    template <typename U>
    Vec3<T> operator/(U s) const {
        double inv = 1.0 / double(s);
        return Vec3<T>(x * inv, y * inv, z * inv);
    }

    template <typename U>
    Vec3<T> operator/=(U s) {
        double inv = 1.0 / double(s);
        x *= inv;
        y *= inv;
        z *= inv;
        return *this;
    }

    bool operator==(const Vec3<T>& v) const { 
        return (x == v.x) and (y == v.y) and (z == v.z); 
    }

    bool operator!=(const Vec3<T>& v) const { 
        return (x != v.x) or (y != v.y) or (z != v.z); 
    }

    Vec3<T> operator-() const { 
        return Vec3<T>(-x, -y, -z); 
    }

    float LengthSquared() const { 
        return x * x + y * y + z * z; 
    }

    float Length() const { 
        return std::sqrt(LengthSquared()); 
    }
};

/**
 * \brief Generic 2-dimensional point data structure
 */

template <typename T>
class Point2 {
  public:
    
    T x, y;

    Point2() { 
        x = y = 0;
    }

    Point2(T _x, T _y) {
        x = _x;
        y = _y;
    }

    Point2<T>& operator=(const Point2<T>& p) {
        x = p.x;
        y = p.y;
        return *this;
    }

    /// Explicit conversion from Point3 to Point2 by droping z
    explicit Point2(const Point3<T>& p) {
        x = p.x;
        y = p.y;
    }

    /// Explicit type conversion of a Point2
    template <typename U> explicit Point2(const Point2<U>& p) {
        x = T(p.x);
        y = T(p.y);
    }

    /// Explicit conversion to a Vec2
    template <typename U> explicit operator Vec3<U>() const {
        return Vec2<U>(x, y);
    }

    Point2<T> operator+(const Vec2<T>& v) const {
        return Point2<T>(x + v.x, y + v.y);
    }

    Point2<T>& operator+=(const Vec2<T>& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Point2<T> operator-(const Vec2<T>& v) const {
        return Point2<T>(x - v.x, y - v.y);
    }

    Point2<T>& operator-=(const Vec2<T>& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vec2<T> operator-(const Point2<T>& p) const {
        return Vec2<T>(x - p.x, y - p.y);
    }

    template <typename U>
    Point2<T> operator*(U s) const {
        return Point2<T>(x * s, y * s);
    }

    template <typename U>
    Point2<T>& operator*=(U s) {
        x *= s;
        y *= s;
        return *this;
    }

    template <typename U>
    Point2<T> operator/(U s) const {
        double inv = 1.0 / double(s);
        return Point2<T>(x * inv, y * inv);
    }

    template <typename U>
    Point2<T>& operator/=(U s) {
        double inv = 1.0 / double(s);
        x *= inv;
        y *= inv;
    }

    Point2<T> operator+(const Point2<T>& p) const {
        return Point2<T>(x + p.x, y + p.y);
    }

    Point2<T>& operator+=(const Point2<T>& p) {
        x += p.x;
        y += p.y;
        return *this;
    }

    bool operator==(const Point2<T>& p) const {
        return (x == p.x) and (y == p.y);
    }

    bool operator!=(const Point2<T>& p) const {
        return (x != p.x) or (y != p.y);
    }
};

/**
 * \brief Generic 3-dimensional point data structure
 */

template <typename T>
class Point3 {
  public:

    T x, y, z;

    Point3() { 
        x = y = z = 0; 
    }

    Point3(T _x, T _y, T _z) {
        x = _x;
        y = _y;
        z = _z;
    }

    Point3<T>& operator=(const Point3<T>& p) {
        x = p.x;
        y = p.y;
        z = p.z;
        return *this;
    }

    /// Explicit type conversion of a Point3
    template <typename U> explicit Point3(const Point3<U>& p) {
        x = T(p.x);
        y = T(p.y);
        z = T(p.z);
    }

    /// Explicit conversion to a Vec3
    template <typename U> explicit operator Vec3<U>() const {
        return Vec3<U>(x, y, z);
    }

    Point3<T> operator+(const Vec3<T>& v) const {
        return Point3<T>(x + v.x, y + v.y, z + v.z);
    }

    Point3<T>& operator+=(const Vec3<T>& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Point3<T> operator-(const Vec3<T>& v) const {
        return Point3<T>(x - v.x, y - v.y), z - v.z;
    }

    Point3<T>& operator-=(const Vec3<T>& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vec3<T> operator-(const Point3<T>& p) const {
        return Vec3<T>(x - p.x, y - p.y, z - p.z);
    }

    template <typename U>
    Point3<T> operator*(U s) const {
        return Point3<T>(x * s, y * s, z * s);
    }

    template <typename U>
    Point3<T>& operator*=(U s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    template <typename U>
    Point3<T> operator/(U s) const {
        double inv = 1.0 / double(s);
        return Point3<T>(x * inv, y * inv, z * inv);
    }

    template <typename U>
    Point3<T>& operator/=(U s) {
        double inv = 1.0 / double(s);
        x *= inv;
        y *= inv;
        z *= inv;
    }

    Point3<T> operator+(const Point3<T>& p) const {
        return Point3<T>(x + p.x, y + p.y, z + p.z);
    }

    Point3<T>& operator+=(const Point3<T>& p) {
        x += p.x;
        y += p.y;
        z += p.z;
        return *this;
    }

    bool operator==(const Point3<T>& p) const {
        return (x == p.x) and (y == p.y) and (z == p.z);
    }

    bool operator!=(const Point3<T>& p) const {
        return (x != p.x) or (y != p.y) or (z != p.z);
    }
};

 /**
 * \brief Generic 3-dimensional normal data structure
 */

template <typename T>
class Normal3 {
  public:
    /// Normal3 public data
    T x, y, z;

    /// Normal3 public methods
    Normal3() {
        x = y = z = 0;
    }

    Normal3(T _x, T _y, T _z) {
        x = _x;
        y = _y;
        z = _z;
    }

    /// Explicit constructor from a Vec3
    explicit Normal3(const Vec3<T>& v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }

    Normal3<T> operator+(const Normal3<T>& n) const {
        return Normal3<T>(x + n.x, y + n.y, z + n.z);
    }

    Normal3<T>& operator+=(const Normal3<T>& n) {
        x += n.x;
        y += n.y;
        z += n.z;
        return *this;
    }

    Normal3<T> operator-(const Normal3<T>& n) const {
        return Normal3<T>(x - n.x, y - n.x, z - n.z);
    }

    Normal3<T>& operator-=(const Normal3<T>& n) {
        x -= n.x;
        y -= n.y;
        z -= n.z;
        return *this;
    }

    template <typename U>
    Normal3<T> operator*(U s) const {
        return Normal3<T>(x * s, y * s, z * s);
    }

    template <typename U>
    Normal3<T>& operator*=(U s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    template <typename U>
    Normal3<T> operator/(U s) const {
        double inv = 1.0 / double(s);
        return Normal3<T>(x * inv, y * inv, z * inv);
    }

    template <typename U>
    Normal3<T>& operator/=(U s) {
        double inv = 1.0 / double(s);
        x /= inv;
        y /= inv;
        z /= inv;
        return *this;
    }

    Normal3<T> operator-() const {
        return Normal3<T>(-x, -y, -z);
    }

    float LengthSquared() const {
        return x * x + y * y + z * z;
    }

    float Length() const {
        return std::sqrt(LengthSquared());
    }
};

/**
 * \brief Ray data structure
 */

class Ray {
  public:
    /// Ray public data
    Point3f o;
    Vec3f d;
    mutable float tMax;
    float time;

    /// Ray public methods
    Ray() {
        tMax = INFINITY;
        time = 0.f;
    }

    Ray(const Point3f& _o, const Vec3f& _d, float _tMax = INFINITY, float _time = 0.f) {
        o = _o;
        d = _d;
        tMax = _tMax;
        time = _time;
    }

    Point3f operator()(float t) const {
        return o + d * t;
    }
};

/**
 * \brief RayDifferential data structure
 */

class RayDifferential: public Ray {
  public:
    /// RayDifferential public data
    bool hasDifferentials;
    Point3f rxOrigin, ryOrigin;
    Vec3f rxDirection, ryDirection;

    /// RayDifferential public method
    RayDifferential() {
        hasDifferentials = false;
    }

    RayDifferential(const Point3f& _o, const Vec3f& _d, float _tMax = INFINITY, float _time = 0.f) 
        : Ray(_o, _d, _tMax, _time) {
        hasDifferentials = false;
    }

    RayDifferential(const Ray& ray): Ray(ray) {
        hasDifferentials = false;
    }

    void ScaleDifferentials(float s) {
        rxOrigin = o + (rxOrigin - o) * s;
        ryOrigin = o + (ryOrigin - o) * s;
        rxDirection = d + (rxDirection - d) * s;
        ryDirection = d + (ryDirection - d) * s;
    }
};

/**
 * \brief Bounds2 data structure
 */

template <typename T>
class Bounds2 {
  public:
    /// Bounds2 public data
    Point2<T> pMin, pMax;


    /// Bounds2 public methods
    Bounds2() {
        T minNum = std::numeric_limits<T>::lowest();
        T maxNum = std::numeric_limits<T>::max();
        pMin = Point2<T>(maxNum, maxNum);
        pMax = Point2<T>(minNum, minNum);
    }

    Bounds2(const Point2<T>& p) {
        pMin = p;
        pMax = p;
    }

    Bounds2(const Point2<T>& p1, const Point2<T>& p2) {
        pMin = Min(p1, p2);
        pMax = Max(p1, p2);
    }

    const Point2<T>& operator[](int i) const {
        return (i == 0) ? pMin : pMax;
    }

    Point2<T>& operator[](int i) {
        return (i == 0) ? pMin : pMax;
    }

    Point2<T> Corner(int corner) const {
        return Point2<T>((*this)[(corner & 1)].x,
                         (*this)[(corner & 2) ? 1 : 0].y);
    }

    Vec2<T> Diagonal() const {
        return pMax - pMin;
    }

    T SurfaceArea() const {
        Vec2<T> d = Diagonal();
        return d.x * d.y;
    }

    int MaximumExtent() const {
        Vec2<T> d = Diagonal();
        if (d.x > d.y) {
            return 0;
        } else {
            return 1;
        }
    }

    Point2<T> Lerp(const Point2<T>& t) const {
        return Point2<T>(Lerp(t.x, pMin.x, pMax.x),
                         Lerp(t.y, pMin.y, pMax.y));
    }

    Point2<T> Offset(const Point2<T>& p) const {
        Vec2<T> o = p - pMin;
        if (pMax.x > pMin.x) {
            o.x /= pMax.x - pMin.x;
        }
        if (pMax.y > pMin.y) {
            o.y /= pMax.y - pMin.y;
        }
        return o;
    }
};

/**
 * \brief Bounds3 data structure
 */

template <typename T>
class Bounds3 {
  public:
    /// Bounds3 public data
    Point3<T> pMin, pMax;

   /// Bounds3 public methods
    Bounds3() {
        T minNum = std::numeric_limits<T>::lowest();
        T maxNum = std::numeric_limits<T>::max();
        pMin = Point3<T>(maxNum, maxNum);
        pMax = Point3<T>(minNum, minNum);
    }

    Bounds3(const Point3<T>& p) {
        pMin = p;
        pMax = p;
    }

    Bounds3(const Point3<T>& p1, const Point3<T>& p2) {
        pMin = Min(p1, p2);
        pMax = Max(p1, p2);
    }

    const Point3<T>& operator[](int i) const {
        return (i == 0) ? pMin : pMax;
    }

    Point3<T>& operator[](int i) {
        return (i == 0) ? pMin : pMax;
    }

    Point3<T> Corner(int corner) const {
        return Point3<T>((*this)[(corner & 1)].x,
                         (*this)[(corner & 2) ? 1 : 0].y,
                         (*this)[(corner & 4) ? 1 : 0].z);
    }

    Vec3<T> Diagonal() const {
        return pMax - pMin;
    }

    T SurfaceArea() const {
        Vec3<T> d = Diagonal();
        return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
    }

    T Volume() const {
        Vec3<T> d = Diagonal();
        return d.x * d.y * d.z;
    }

    int MaximumExtent() const {
        Vec3<T> d = Diagonal();
        if (d.x > d.y and d.x > d.z) {
            return 0;
        } else if (d.y > d.z) {
            return 1;
        } else {
            return 2;
        }
    }

    Point3<T> Lerp(const Point3<T>& t) const {
        return Point3<T>(Lerp(t.x, pMin.x, pMax.x),
                         Lerp(t.y, pMin.y, pMax.y),
                         Lerp(t.z, pMin.z, pMax.z));
    }

    Point3<T> Offset(const Point3<T>& p) const {
        Vec3<T> o = p - pMin;
        if (pMax.x > pMin.x) {
            o.x /= pMax.x - pMin.x;
        }
        if (pMax.y > pMin.y) {
            o.y /= pMax.y - pMin.y;
        }
        if (pMax.z > pMin.z) {
            o.z /= pMax.z - pMin.z;
        }
        return o;
    }

    void BoudingSphere(Point3<T>* center, float* radius) {
        *center = (pMin + pMax) / 2;
        *radius = Inside(*center, *this) ? Distance(*center, pMax) : 0;
    }
};

/**
 * \brief Interator for Bounds2i 
 */

class Bounds2iIterator: public std::forward_iterator_tag {
  public:
    /// Public Bounds2iIter methods
    Bounds2iIterator(const Bounds2i& _b, const Point2i& _p): p(_p), b(&_b) {}
    
    Bounds2iIterator operator++() {
        Iterate();
        return *this;
    }

    Bounds2iIterator operator++(int) {
        Bounds2iIterator old = *this;
        Iterate();
        return old;
    }

    bool operator==(const Bounds2iIterator &bi) const {
        return p == bi.p && b == bi.b;
    }

    bool operator!=(const Bounds2iIterator &bi) const {
        return p != bi.p or b != bi.b;
    }

    Point2i operator*() const { 
        return p; 
    }

  private:
    /// Private Bounds2iIter data
    Point2i p;
    const Bounds2i* b;

    /// Private Bounds2iIter methods
    void Iterate() {
        ++p.x;
        if (p.x == b->pMax.x) {
            p.x = b->pMin.x;
            ++p.y;
        }
    }

};

/**
 * \brief Vector inline functions
 */

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vec2<T>& v) {
    os << v.x << " " << v.y;
    return os;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vec3<T>& v) {
    os << v.x << " " << v.y << " " << v.z;
    return os;
}

template <typename T, typename U>
inline Vec2<T> operator*(U s, const Vec2<T>& v) {
    return v * s;
}

template <typename T, typename U>
inline Vec3<T> operator*(U s, const Vec3<T>& v) {
    return v * s;
}

template <typename T>
inline Vec2<T> Abs(const Vec2<T>& v) {
    return Vec2<T>(std::abs(v.x), std::abs(v.y));
}

template <typename T>
inline Vec3<T> Abs(const Vec3<T>& v) {
    return Vec3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
}

template <typename T>
inline T Dot(const Vec2<T>& v1, const Vec2<T>& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

template <typename T>
inline T Dot(const Vec3<T>& v1, const Vec3<T>& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T>
inline T AbsDot(const Vec2<T>& v1, const Vec2<T>& v2) {
    return std::abs(Dot(v1, v2));
}

template <typename T>
inline T AbsDot(const Vec3<T>& v1, const Vec3<T>& v2) {
    return std::abs(Dot(v1, v2));
}

/// Note: Vec2 does not have a well defined cross product
template <typename T>
inline Vec3<T> Cross(const Vec3<T>& v1, const Vec3<T>& v2) {
    return Vec3<T>((v1.y * v2.z) - (v1.z * v2.y),
                   (v1.z * v2.x) - (v1.x * v2.z),
                   (v1.x * v2.y) - (v1.y * v2.x));
}

template <typename T>
inline Vec2<T> Normalize(const Vec2<T>& v) {
    return v / v.Length();
}

template <typename T>
inline Vec3<T> Normalize(const Vec3<T>& v) { 
    return v / v.Length(); 
}

template <typename T>
inline T MinComponent(const Vec2<T>& v) {
    return std::min(v.x, v.y);
}

template <typename T>
inline T MinComponent(const Vec3<T>& v) {
    return std::min(v.x, std::min(v.y, v.z));
}

template <typename T>
inline T MaxComponent(const Vec2<T>& v) {
    return std::max(v.x, v.y);
}

template <typename T>
inline T MaxComponent(const Vec3<T>& v) {
    return std::max(v.x, std::max(v.y, v.z));
}

template <typename T>
inline int MinDimension(const Vec2<T>& v) {
    if (v.x < v.y)
        return 0;
    return 1;
}

template <typename T>
inline int MinDimension(const Vec3<T>& v) {
    if (v.x < v.y)
        if (v.x < v.z)
            return 0;
        return 1;
    if (v.y < v.z)
        return 1;
    return 2;
}

template <typename T>
inline int MaxDimension(const Vec2<T>& v) {
    if (v.x > v.y) 
        return 0;
    return 1;
}

template <typename T>
inline int MaxDimension(const Vec3<T>& v) {
    if (v.x > v.y)
        if (v.x > v.z)
            return 0;
        return 1;
    if (v.y > v.z)
        return 1;
    return 2;
}

template <typename T>
inline Vec2<T> Min(const Vec2<T>& v1, const Vec2<T>& v2) {
    return Vec2<T>(std::min(v1.x, v2.x), std::min(v1.y, v2.y));
}

template <typename T>
inline Vec3<T> Min(const Vec3<T>& v1, const Vec3<T>& v2) {
    return Vec3<T>(std::min(v1.x, v2.x), std::min(v1.y, v2.y), std::min(v1.z, v2.z));
}

template <typename T>
Vec2<T> Max(const Vec2<T>& v1, const Vec2<T>& v2) {
    return Vec2<T>(std::max(v1.x, v2.x), std::max(v1.y, v2.y));
}

template <typename T>
Vec3<T> Max(const Vec3<T>& v1, const Vec3<T>& v2) {
    return Vec3<T>(std::max(v1.x, v2.x), std::max(v1.y, v2.y), std::max(v1.z, v2.z));
}

template <typename T>
inline Vec2<T> Permute(const Vec3<T>& v, int x, int y) {
    return Vec2<T>(v[x], v[y]);
}

template <typename T>
inline Vec3<T> Permute(const Vec3<T>& v, int x, int y, int z) {
    return Vec3<T>(v[x], v[y], v[z]);
}

/// Note: assumes v1 is normalized before calling
template <typename T>
inline void CoordinateSystem(const Vec2<T>& v1, Vec2<T>* v2) {
    if (std::abs(v1.x) > std::abs(v1.y)) {
        *v2 = Vec2<T>(-v1.y, v1.x);
    } else {
        *v2 = Vec2<T>(v1.y, -v1.x);
    }
}

/// Note: assumes v1 is normalized before calling
template <typename T>
inline void CoordinateSystem(const Vec3<T>& v1, Vec3<T>* v2, Vec3<T>* v3) {
    if (std::abs(v1.x) > std::abs(v1.y)) {
        *v2 = Vec3<T>(-v1.z, 0, v1.x) / std::sqrt(v1.x * v1.x + v1.z * v1.z);
    } else {
        *v2 = Vec3<T>(0, v1.z, -v1.y) / std::sqrt(v1.y * v1.y + v1.z * v1.z);
    }
    *v3 = Cross(v1, *v2);
}

/**
 * \brief Point inline functions
 */

template <typename T>
inline float Distance(const Point2<T>& p1, const Point2<T>& p2) {
    return (p1 - p2).Length();
}

template <typename T>
inline float Distance(const Point3<T>& p1, const Point3<T>& p2) {
    return (p1 - p2).Length();
}

template <typename T>
inline float DistanceSquared(const Point2<T>& p1, const Point2<T>& p2) {
    return (p1 - p2).LengthSquared();
}

template <typename T>
inline float DistanceSquared(const Point3<T>& p1, const Point3<T>& p2) {
    return (p1 - p2).LengthSquared();
}

template <typename T>
inline Point2<T> Lerp(float t, const Point2<T>& p0, const Point2<T>& p1) {
    return (1 - t) * p0 + t * p1;
}

template <typename T>
inline Point3<T> Lerp(float t, const Point3<T>& p0, const Point3<T>& p1) {
    return (1 - t) * p0 + t * p1;
}

template <typename T>
inline Point2<T> Min(const Point2<T>& p1, const Point2<T>& p2) {
    return Point2<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y));
}

template <typename T>
inline Point3<T> Min(const Point3<T>& p1, const Point3<T>& p2) {
    return Point3<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z));
}

template <typename T>
inline Point2<T> Max(const Point2<T>& p1, const Point2<T>& p2) {
    return Point2<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y));
}

template <typename T>
inline Point3<T> Max(const Point3<T>& p1, const Point3<T>& p2) {
    return Point3<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z));
}

template <typename T>
inline Point2<T> Floor(const Point2<T>& p) {
    return Point2<T>(std::floor(p.x), std::floor(p.y));
}

template <typename T>
inline Point3<T> Floor(const Point3<T>& p) {
    return Point3<T>(std::floor(p.x), std::floor(p.y), std::floor(p.z));
}

template <typename T>
inline Point2<T> Ceil(const Point2<T>& p) {
    return Point2<T>(std::ceil(p.x), std::ceil(p.y));
}

template <typename T>
inline Point3<T> Ceil(const Point3<T>& p) {
    return Point3<T>(std::ceil(p.x), std::ceil(p.y), std::ceil(p.z));
}

template <typename T>
inline Point2<T> Abs(const Point2<T>& p) {
    return Point2<T>(std::abs(p.x), std::abs(p.y));
}

template <typename T>
inline Point3<T> Abs(const Point3<T>& p) {
    return Point3<T>(std::abs(p.x), std::abs(p.y), std::abs(p.z));
}

template <typename T>
inline Point2<T> Permute(const Point2<T>& p, int x, int y) {
    return Point2<T>(p[x], p[y]);
}

template <typename T>
inline Point3<T> Permute(const Point3<T>& p, int x, int y, int z) {
    return Point3<T>(p[x], p[y], p[z]);
}

/**
 * \brief Normal inline functions
 */

template <typename T, typename U>
inline Normal3<T> operator*(U s, const Normal3<T>& n) {
    return n * s;
}

template <typename T>
inline Normal3<T> Normalize(const Normal3<T>& n) {
    return n / n.Length();
}

template <typename T>
inline float Dot(const Normal3<T>& n1, const Normal3<T>& n2) {
    return n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
}

template <typename T>
inline float Dot(const Normal3<T>& n, const Vec3<T>& v) {
    return n.x * v.x + n.y * v.y + n.z * v.z;
}

template <typename T>
inline float Dot(const Vec3<T>& v, const Normal3<T>& n) {
    return n.x * v.x + n.y * v.y + n.z * v.z;
}

template <typename T>
inline float AbsDot(const Normal3<T>& n1, const Normal3<T>& n2) {
    return std::abs(Dot(n1, n2));
}

template <typename T>
inline float AbsDot(const Normal3<T>& n, const Vec3<T>& v) {
    return std::abs(Dot(n, v));
}

template <typename T>
inline float AbsDot(const Vec3<T>& v, const Normal3<T>& n) {
    return std::abs(Dot(v, n));
}

template <typename T>
inline Normal3<T> Faceforward(const Normal3<T>& n, const Vec3<T>& v) {
    return (Dot(n, v) < 0.f) ? -n : n;
}

template <typename T>
inline Vec3<T> Faceforward(const Vec3<T>& v, const Normal3<T>& n) {
    return (Dot(v, n) < 0.f) ? -v : v;
}

template <typename T>
inline Normal3<T> Faceforward(const Normal3<T>& n1, const Normal3<T>& n2) {
    return (Dot(n1, n2) < 0.f) ? -n1 : n1;
}

template <typename T>
inline Vec3<T> Faceforward(const Vec3<T>& v1, const Vec3<T>& v2) {
    return (Dot(v1, v2) < 0.f) ? -v1 : v2;
}

/**
 * \brief Bounds inline functions
 */

template <typename T>
inline Bounds2<T> Union(const Bounds2<T>& b, const Point2<T>& p) {
    return Bounds2<T>(Min(b, p), Max(b, p));
}

template <typename T>
inline Bounds3<T> Union(const Bounds3<T>& b, const Point3<T>& p) {
    return Bounds3<T>(Min(b.pMin, p), Max(b.pMax, p));
}

template <typename T>
inline Bounds2<T> Union(const Bounds2<T>& b1, const Bounds2<T>& b2) {
    return Bounds2<T>(Min(b1.pMin, b2.pMin), Max(b1.pMax, b2.pMax));
}

template <typename T>
inline Bounds3<T> Union(const Bounds3<T>& b1, const Bounds3<T>& b2) {
    return Bounds3<T>(Min(b1.pMin, b2.pMin), Max(b1.pMax, b2.pMax));
}

template <typename T>
inline Bounds2<T> Intersect(const Bounds2<T>& b1, const Bounds2<T>& b2) {
    return Bounds2<T>(Max(b1.pMin, b2.pMin), Min(b1.pMax, b2.pMax));
}

template <typename T>
inline Bounds3<T> Intersect(const Bounds3<T>& b1, const Bounds3<T>& b2) {
    return Bounds3<T>(Max(b1.pMin, b2.pMin), Min(b1.pMax, b2.pMax));
}

template <typename T>
inline bool Overlaps(const Bounds2<T>& b1, const Bounds2<T>& b2) {
    bool x = (b1.pMax.x >= b2.pMin.x) and (b1.pMin.x <= b2.pMax.x);
    bool y = (b1.pMax.y >= b2.pMin.y) and (b1.pMin.y <= b2.pMax.y);
    return (x and y);
}

template <typename T>
inline bool Overlaps(const Bounds3<T>& b1, const Bounds3<T>& b2) {
    bool x = (b1.pMax.x >= b2.pMin.x) and (b1.pMin.x <= b2.pMax.x);
    bool y = (b1.pMax.y >= b2.pMin.y) and (b1.pMin.y <= b2.pMax.y);
    bool z = (b1.pMax.z >= b2.pMin.z) and (b1.pMin.z <= b2.pMax.z);
    return (x and y and z);
}

template <typename T>
inline bool Inside(const Point2<T>& p, const Bounds2<T>& b) {
    return (p.x >= b.pMin.x and p.x <= b.pMax.x) and
           (p.y >= b.pMin.y and p.y <= b.pMax.y);
}

template <typename T>
inline bool Inside(const Point3<T>& p, const Bounds3<T>& b) {
    return (p.x >= b.pMin.x and p.x <= b.pMax.x) and
           (p.y >= b.pMin.y and p.y <= b.pMax.y) and
           (p.z >= b.pMin.z and p.z <= b.pMax.z);
}

template <typename T>
inline bool InsideExclusive(const Point2<T>& p, const Bounds2<T>& b) {
    return (p.x >= b.pMin.x and p.x < b.pMax.x) and
           (p.y >= b.pMin.y and p.y < b.pMax.y);
}

template <typename T>
inline bool InsideExclusive(const Point3<T>& p, const Bounds3<T>& b) {
    return (p.x >= b.pMin.x and p.x < b.pMax.x) and
           (p.y >= b.pMin.y and p.y < b.pMax.y) and
           (p.z >= b.pMin.z and p.z < b.pMax.z);
}

template <typename T, typename U>
inline Bounds2<T> Expand(const Bounds2<T>& b, U delta) {
    return Bounds2<T>(b.pMin - Vec2<T>(delta, delta),
                      b.pMax + Vec2<T>(delta, delta));
}

template <typename T, typename U>
inline Bounds3<T> Expand(const Bounds3<T>& b, U delta) {
    return Bounds3<T>(b.pMin - Vec3<T>(delta, delta, delta),
                      b.pMax + Vec3<T>(delta, delta, delta));
}

/**
 * \breif Bounds2iIter inline functions
 */

inline Bounds2iIterator begin(const Bounds2i& b) {
    return Bounds2iIterator(b, b.pMin);
}

inline Bounds2iIterator end(const Bounds2i& b) {
    // Normally, the ending point is at the minimum x value and one past
    // the last valid y value.
    Point2i pEnd(b.pMin.x, b.pMax.y);
    // However, if the bounds are degenerate, override the end point to
    // equal the start point so that any attempt to iterate over the bounds
    // exits out immediately.
    if (b.pMin.x >= b.pMax.x or b.pMin.y >= b.pMax.y)
        pEnd = b.pMin;
    return Bounds2iIterator(b, pEnd);
}

HEIMDALL_NAMESPACE_END
