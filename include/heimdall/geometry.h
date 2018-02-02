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

    double LengthSquared() { 
        return x * x + y * y; 
    }

    double Length() { 
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

    double LengthSquared() const { 
        return x * x + y * y + z * z; 
    }

    double Lenght() const { 
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

    Point2() { x = y = 0;}
    Point2(T _x, T _y) {
        x = _x;
        y = _y;
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

    Point3() { x = y = z = 0; }
    Point3(T _x, T _y, T _z) {
        x = _x;
        y = _y;
        z = _z;
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

    double LengthSquared() const {
        return x * x + y * y + z * z;
    }

    double Length() const {
        return std::sqrt(LengthSquared());
    }
};

/**
 * \breief Vector inline functions
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
inline double Distance(const Point2<T>& p1, const Point2<T>& p2) {
    return (p1 - p2).Length();
}

template <typename T>
inline double Distance(const Point3<T>& p1, const Point3<T>& p2) {
    return (p1 - p2).Length();
}

template <typename T>
inline double DistanceSquared(const Point2<T>& p1, const Point2<T>& p2) {
    return (p1 - p2).LengthSquared();
}

template <typename T>
inline double DistanceSquared(const Point3<T>& p1, const Point3<T>& p2) {
    return (p1 - p2).LengthSquared();
}

template <typename T>
inline Point2<T> Lerp(double t, const Point2<T>& p0, const Point2<T>& p1) {
    return (1 - t) * p0 + t * p1;
}

template <typename T>
inline Point3<T> Lerp(double t, const Point3<T>& p0, const Point3<T>& p1) {
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
inline double Dot(const Normal3<T>& n1, const Normal3<T>& n2) {
    return n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
}

template <typename T>
inline double Dot(const Normal3<T>& n, const Vec3<T>& v) {
    return n.x * v.x + n.y * v.y + n.z * v.z;
}

template <typename T>
inline double Dot(const Vec3<T>& v, const Normal3<T>& n) {
    return n.x * v.x + n.y * v.y + n.z * v.z;
}

template <typename T>
inline double AbsDot(const Normal3<T>& n1, const Normal3<T>& n2) {
    return std::abs(Dot(n1, n2));
}

template <typename T>
inline double AbsDot(const Normal3<T>& n, const Vec3<T>& v) {
    return std::abs(Dot(n, v));
}

template <typename T>
inline double AbsDot(const Vec3<T>& v, const Normal3<T>& n) {
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

HEIMDALL_NAMESPACE_END
