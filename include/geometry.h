#pragma once

#include <iostream>
#include <cmath>

template <typename T>
class Vec3 {
public:
    T x, y, z;

    Vec3() { x = y = z = 0; }
    Vec3(T _x, T _y, T _z) {
        x = _x;
        y = _y;
        z = _z;
    }

    T& operator[](int i) {
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }

    Vec3<T> operator+(const Vec3<T>& v) const { return Vec3<T>(x + v.x, y + v.y, z + v.z); }
    Vec3<T>& operator+=(const Vec3<T>& v) {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }

    Vec3<T> operator-(const Vec3<T>& v) const { return Vec3<T>(x - v.x, y - v.y, z - v.z); }
    Vec3<T>& operator-=(const Vec3<T>& v) {
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }

    Vec3<T> operator*(T s) const { return Vec3<T>(s * x, s * y, s * z); }
    Vec3<T>& operator*=(T s) {
        x *= s; y *= s; z *= s;
        return *this;
    }

    Vec3<T> operator/(T s) const {
        double inv = double(1 / s);
        return Vec3<T>(x * inv, y * inv, z * inv);
    }
    Vec3<T>& operator/=(T s) {
        double inv = double(1 / s);
        x *= inv; y *= inv; z *= inv;
        return *this;
    }

    Vec3<T> operator-() const { return Vec3<T>(-x, -y, -z); }

    double LengthSquared() const { return x * x + y * y + z * z; }
    double Lenght() const { return std::sqrt(LengthSquared()); }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vec3<T>& v) {
    os << v.x << " " << v.y << " " << v.z;
    return os;
}

template <typename T>
Vec3<T> Abs(const Vec3<T>& v) {
    return Vec3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
}

template <typename T>
inline T Dot(const Vec3<T>& v1, const Vec3<T>& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T>
inline T AbsDot(const Vec3<T>& v1, const Vec3<T>& v2) {
    return std::abs(Dot(v1, v2));
}

template <typename T>
inline Vec3<T> Cross(const Vec3<T>& v1, const Vec3<T>& v2) {
    return Vec3<T>((v1.y * v2.z) - (v1.z * v2.y),
                   (v1.z * v2.x) - (v1.x * v2.z),
                   (v1.x * v2.y) - (v1.y * v2.x));
}

template <typename T>
inline Vec3<T> Normalize(const Vec3<T>& v) { return v / v.Length(); }

template <typename T>
T MinComponent(const Vec3<T>& v) {
    return std::min(v.x, std::min(v.y, v.z));
}

template <typename T>
T MaxComponent(const Vec3<T>& v) {
    return std::max(v.x, std::max(v.y, v.z));
}

template <typename T>
int MinDimension(const Vec3<T>& v) {
    if (v.x < v.y)
        if (v.x < v.z)
            return 0;
        return 1;
    if (v.y < v.z)
        return 1;
    return 2;
}

template <typename T>
int MaxDimension(const Vec3<T>& v) {
    if (v.x > v.y)
        if (v.x > v.z)
            return 0;
        return 1;
    if (v.y > v.z)
        return 1;
    return 2;
}

template <typename T>
Vec3<T> Min(const Vec3<T>& v1, const Vec3<T>& v2) {
    return Vec3<T>(std::min(v1.x, v2.x), std::min(v1.y, v2.y), std::min(v1.z, v2.z));
}

template <typename T>
Vec3<T> Max(const Vec3<T>& v1, const Vec3<T>& v2) {
    return Vec3<T>(std::max(v1.x, v2.x), std::max(v1.y, v2.y), std::max(v1.z, v2.z));
}

template <typename T>
Vec3<T> Permute(const Vec3<T>& v, int x, int y, int z) {
    return Vec3<T>(v[x], v[y], v[z]);
}

template <typename T>
inline void CoordinateSystem(const Vec3<T>& v1, Vec3<T>* v2, Vec3<T>* v3) {
    if (std::abs(v1.x) > std::abs(v1.y)) {
        *v2 = Vec3<T>(-v1.z, 0, v1.x) / std::sqrt(v1.x * v1.x + v1.z * v1.z);
    } else {
        *v2 = Vec3<T>(0, v1.z, -v1.y) / std::sqrt(v1.y * v1.y + v1.z * v1.z);
    }
    *v3 = Cross(v1, *v2);
}

typedef Vec3<double> Vec3f;
typedef Vec3<int> Vec3i;
