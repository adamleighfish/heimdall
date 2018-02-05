#pragma once

#include "heimdall/common.h"
#include "heimdall/geometry.h"

HEIMDALL_NAMESPACE_BEGIN

class Quaternion {
  public:
  	/// Quaternion public data
  	Vec3f v;
  	float w;

  	/// Quaternion public methods
  	Quaternion();
  	Quaternion(const Vec3f& _v, float _w);
  	Quaternion(const Transform& t);

  	Quaternion  operator+(const Quaternion& q) const;
  	Quaternion& operator+=(const Quaternion& q);
  	Quaternion  operator-(const Quaternion& q) const;
  	Quaternion& operator-=(const Quaternion& q);
  	Quaternion  operator*(float s) const;
  	Quaternion& operator*=(float s);
  	Quaternion  operator/(float s) const;
  	Quaternion& operator/=(float s);
  	Quaternion  operator-() const;

  	Transform ToTransform() const;
};

Quaternion operator*(float s, const Quaternion& q);
Quaternion Slerp(float t, const Quaternion& q1, const Quaternion& q2);
Quaternion Normalize(const Quaternion& q);
float Dot(const Quaternion& q1, const Quaternion& q2);


HEIMDALL_NAMESPACE_END