#include "heimdall/quaternion.h"
#include "heimdall/transform.h"

HEIMDALL_NAMESPACE_BEGIN

Quaternion::Quaternion() {
	w = 1;
}

Quaternion::Quaternion(const Vec3f& _v, float _w) {
	v = _v;
	w = _w;
}

Quaternion::Quaternion(const Transform& t) {
	const Matrix& m = t.m;
	if (m.m[0][0] + m.m[1][1] + m.m[2][2] > 0.0f) {

		float t = m.m[0][0] + m.m[1][1] + m.m[2][2] + 1.0f;
		float s = InvSqrt(t) * 0.5f;

		v.x = (m.m[1][2] - m.m[2][1]) * s;
		v.y = (m.m[2][0] - m.m[0][2]) * s;
		v.z = (m.m[0][1] - m.m[1][0]) * s;
		w = s * t;

	} else if (m.m[0][0] > m.m[1][1] and m.m[0][0] > m.m[2][2]) {

		float t = m.m[0][0] - m.m[1][1] - m.m[2][2] + 1.0f;
		float s = InvSqrt(t) * 0.5f;

		v.x = (m.m[1][2] - m.m[2][1]) * s;
		v.y = (m.m[2][0] + m.m[0][2]) * s;
		v.z = (m.m[0][1] + m.m[1][0]) * s;
		w = s * t;

	} else if (m.m[1][1] > m.m[0][0] and m.m[1][1] > m.m[2][2]) {

		float t = -m.m[0][0] + m.m[1][1] - m.m[2][2] + 1.0f;
		float s = InvSqrt(t) * 0.5f;

		v.x = (m.m[1][2] + m.m[2][1]) * s;
		v.y = (m.m[2][0] - m.m[0][2]) * s;
		v.z = (m.m[0][1] + m.m[1][0]) * s;
		w = s * t;

	} else {

		float t = -m.m[0][0] - m.m[1][1] + m.m[2][2] + 1.0f;
		float s = InvSqrt(t) * 0.5f;

		v.x = (m.m[1][2] + m.m[2][1]) * s;
		v.y = (m.m[2][0] + m.m[0][2]) * s;
		v.z = (m.m[0][1] - m.m[1][0]) * s;
		w = s * t;

	}
}

Quaternion Quaternion::operator+(const Quaternion& q) const {
	return Quaternion(v + q.v, w + q.w);
}

Quaternion& Quaternion::operator+=(const Quaternion& q) {
	v += q.v;
	w += q.w;
	return *this;
}

Quaternion Quaternion::operator-(const Quaternion& q) const {
	return Quaternion(v - q.v, w - q.w);
}

Quaternion& Quaternion::operator-=(const Quaternion& q) {
	v -= q.v;
	w -= q.w;
	return *this;
}

Quaternion Quaternion::operator*(float s) const {
	return Quaternion(v * s, w * s);
}

Quaternion& Quaternion::operator*=(float s) {
	v *= s;
	w *= s;
	return *this;
}

Quaternion Quaternion::operator/(float s) const {
	return Quaternion(v / s, w / s);
}

Quaternion& Quaternion::operator/=(float s) {
	v /= s;
	w /= s;
	return *this;
}

Quaternion Quaternion::operator-() const {
	return Quaternion(-v, -w);
}

/// Quaternion to Transform method, optimized for FPUs
Transform Quaternion::ToTransform() const {
	Matrix m;

	float x2 = v.x + v.x;
	float y2 = v.y + v.y;
	float z2 = v.z + v.z;

	{
		float xx2 = v.x * x2;
		float yy2 = v.y * y2;
		float zz2 = v.z * z2;

		m.m[0][0] = 1.0f - yy2 - zz2;
		m.m[1][1] = 1.0f - xx2 - zz2;
		m.m[2][2] = 1.0f - xx2 - yy2;
	}

	{
		float yz2 = v.y * z2;
		float wx2 = w * x2;

		m.m[2][1] = yz2 - wx2;
		m.m[1][2] = yz2 + wx2;
	}

	{
		float xy2 = v.x * y2;
		float wz2 = w * z2;

		m.m[1][0] = xy2 - wz2;
		m.m[0][1] = xy2 + wz2;
	}

	{
		float xz2 = v.x * z2;
		float wy2 = w * y2;

		m.m[0][2] = xz2 - wy2;
		m.m[2][0] = xz2 + wy2;
	}

	return Transform(m);
}

Quaternion operator*(float s, const Quaternion& q) {
	return q * s;
}

Quaternion Slerp(float t, const Quaternion& q1, const Quaternion& q2) {
	float cosTheta = Dot(q1, q2);
	if (cosTheta > 0.9995f) {

		return Normalize((1 - t) * q1 + t * q2);

	} else {

		float theta = std::acos(Clamp(cosTheta, -1, 1));
		float thetaP = theta * t;
		Quaternion qPerp = Normalize(q2 - q1 * cosTheta);
		return q1 * std::cos(thetaP) + qPerp * std::sin(thetaP);

	}
}

Quaternion Normalize(const Quaternion& q) {
	return q / std::sqrt(Dot(q, q));
}

float Dot(const Quaternion& q1, const Quaternion& q2) {
	return Dot(q1.v, q2.v) + q1.w * q2.w;
}




HEIMDALL_NAMESPACE_END