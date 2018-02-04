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

/// Basic data stuctures with common type aliases
typedef Vec2<double>    Vec2f;
typedef Vec3<double>    Vec3f;
typedef Vec2<int>       Vec2i;
typedef Vec3<int>       Vec3i;
typedef Point2<double>  Point2f;
typedef Point3<double>  Point3f;
typedef Point2<int>		Point2i;
typedef Point3<int>		Point3i;
typedef Normal2<double> Normal2f;
typedef Normal3<double> Normal3f;
typedef Bounds2<double> Bounds2f;
typedef Bounds3<double> Bounds3f;
typedef Bounds2<int>	Bounds2i;
typedef Bounds3<int>	Bounds3i;

/// Common functions across all files

inline double Lerp(double t, double v1, double v2) {
	return (1 - t) * v1 + t * v2;
}

/// Import cout, cerr, endl for debugging purposes
using std::cout;
using std::cerr;
using std::endl;

HEIMDALL_NAMESPACE_END