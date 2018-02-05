#pragma once

/// Common includes across all files
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <limits>
#include <iterator>
#include <cstring>

/// Convenient definitions
#define HEIMDALL_NAMESPACE_BEGIN namespace heimdall {
#define HEIMDALL_NAMESPACE_END }

/// Error epsilon for ray-surface interaction
#define Epsilon 1e-4f

/// Useful constants
#undef M_PI

#define M_PI         3.14159265358979323846f
#define INV_PI       0.31830988618379067154f
#define INV_TWOPI    0.15915494309189533577f
#define INV_FOURPI   0.07957747154594766788f
#define SQRT_TWO     1.41421356237309504880f
#define INV_SQRT_TWO 0.70710678118654752440f

HEIMDALL_NAMESPACE_BEGIN

/// Forward declarations
template <typename T> class Vec2;
template <typename T> class Vec3;
template <typename T> class Point2;
template <typename T> class Point3;
template <typename T> class Normal2;
template <typename T> class Normal3;
template <typename T> class Bounds2;
template <typename T> class Bounds3;
class Matrix;
class Transform;
class Quaternion;

/// Basic data stuctures with common type aliases
typedef Vec2<float>        Vec2f;
typedef Vec3<float>        Vec3f;
typedef Vec2<int>          Vec2i;
typedef Vec3<int>          Vec3i;
typedef Point2<float>    Point2f;
typedef Point3<float>    Point3f;
typedef Point2<int>		 Point2i;
typedef Point3<int>		 Point3i;
typedef Normal2<float>  Normal2f;
typedef Normal3<float>  Normal3f;
typedef Bounds2<float>  Bounds2f;
typedef Bounds3<float>  Bounds3f;
typedef Bounds2<int>	Bounds2i;
typedef Bounds3<int>	Bounds3i;

/// Common functions across all files

inline float Lerp(float t, float v1, float v2) {
	return (1 - t) * v1 + t * v2;
}

inline float InvSqrt(float x) {
	float xhalf = x * 0.5f;
	int i = *(int*)&x;				// store floating-point bits in integer
	i = 0x5f3759df - (i >> 1);  	// initial guess for Newton's method
    x = *(float*)&i;            	// convert new bits into float
    x = x * (1.5f - xhalf * x * x); // One round of Newton's method
    return x;
}

template <typename T, typename U, typename V>
inline T Clamp(T val, U low, V high) {
    if (val < low) {
        return low;
    } else if (val > high) {
        return high;
    }
    return val;
}

/// Import cout, cerr, endl for debugging purposes
using std::cout;
using std::cerr;
using std::endl;

HEIMDALL_NAMESPACE_END