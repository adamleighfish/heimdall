#include "heimdall/transform.h"

HEIMDALL_NAMESPACE_BEGIN

/**
 * \breif Transform method definitions
 */

Transform::Transform() {}

Transform::Transform(const float mat[4][4]) {
	m = Matrix(mat[0][0], mat[0][1], mat[0][2], mat[0][3],
			   mat[1][0], mat[1][1], mat[1][2], mat[1][3],
			   mat[2][0], mat[2][1], mat[2][2], mat[2][3],
			   mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
	mInv = Inverse(m);
}

Transform::Transform(const Matrix& _m) {
	m = _m;
	mInv = Inverse(m);
}

Transform::Transform(const Matrix& _m, const Matrix& _mInv) {
	m = _m;
	mInv = _mInv;
}

bool Transform::isIdentity() const {
	return m.m[0][0] == 1.f and m.m[0][1] == 0.f and m.m[0][2] == 0.f and m.m[0][3] == 0.f and
		   m.m[1][0] == 0.f and m.m[1][1] == 1.f and m.m[1][2] == 0.f and m.m[3][3] == 0.f and
		   m.m[2][0] == 0.f and m.m[2][1] == 0.f and m.m[2][2] == 1.f and m.m[3][3] == 0.f and
		   m.m[3][0] == 0.f and m.m[3][1] == 0.f and m.m[3][2] == 0.f and m.m[3][3] == 1.f;
}

bool Transform::SwapsHandedness() const {
	float det = m.m[0][0] * (m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1]) -
				m.m[1][0] * (m.m[1][0] * m.m[2][2] - m.m[1][2] * m.m[2][0]) +
				m.m[0][2] * (m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0]);
	return det < 0.0f;
}

bool Transform::operator==(const Transform& t) const {
	return m == t.m and mInv == t.mInv;
}

bool Transform::operator!=(const Transform& t) const {
	return m != t.m or mInv != t.mInv;
}

Transform Transform::operator*(const Transform& t) const {
	return Transform(m * t.m, t.mInv * mInv);
}

Transform Inverse(const Transform& t) {
	return Transform(t.mInv, t.m);
}

Transform Transpose(const Transform& t) {
	return Transform(Transpose(t.m), Transpose(t.mInv));
}

Transform Translate(const Vec3f& delta) {
	Matrix m(1, 0, 0, delta.x,
			 0, 1, 0, delta.y,
			 0, 0, 1, delta.z,
			 0, 0, 0, 1);
	Matrix mInv(1, 0, 0, -delta.x,
		 		0, 1, 0, -delta.y,
		 		0, 0, 1, -delta.z,
		 		0, 0, 0, 1);

	return Transform(m, mInv);
}

Transform Scale(float x, float y, float z) {
	Matrix m(x, 0, 0, 0,
			 0, y, 0, 0,
			 0, 0, z, 0, 
			 0, 0, 0, 1);
	Matrix mInv(1/x, 0,   0,   0,
			    0,   1/y, 0,   0, 
			    0,   0,   1/z, 0,
			    0,   0,   0,   1);
	return Transform(m, mInv);
}

Transform RotateX(float theta) {
	float sinTheta = std::sin(Radians(theta));
	float cosTheta = std::cos(Radians(theta));
	Matrix m(1, 0,         0,         0,
			 0, cosTheta, -sinTheta,  0,
			 0, sinTheta,  cosTheta,  0,
			 0, 0,		   0,         1);
	return Transform(m, Transpose(m));
}

Transform RotateY(float theta) {
	float sinTheta = std::sin(Radians(theta));
	float cosTheta = std::cos(Radians(theta));
	Matrix m(cosTheta,  0, sinTheta, 0,
			 0,	        1, 0,        0,
			-sinTheta,  0, cosTheta, 0,
			 0,         0, 0,        1);
	return Transform(m, Transpose(m));
}

Transform RotateZ(float theta) {
	float sinTheta = std::sin(Radians(theta));
	float cosTheta = std::cos(Radians(theta));
	Matrix m(cosTheta, -sinTheta, 0, 0,
			 sinTheta,  cosTheta, 0, 0,
			 0,			0, 		  1, 0,
			 0, 		0, 		  0, 1);
	return Transform(m, Transpose(m));
}

Transform Rotate(float theta, const Vec3f& axis) {
	Vec3f a = Normalize(axis);
	float sinTheta = std::sin(Radians(theta));
	float cosTheta = std::cos(Radians(theta));
	Matrix m;

	// Compute rotation of first basis vector
    m.m[0][0] = a.x * a.x + (1 - a.x * a.x) * cosTheta;
    m.m[0][1] = a.x * a.y * (1 - cosTheta) - a.z * sinTheta;
    m.m[0][2] = a.x * a.z * (1 - cosTheta) + a.y * sinTheta;
    m.m[0][3] = 0;

    // Compute rotation of second basis vector
    m.m[1][0] = a.x * a.y * (1 - cosTheta) + a.z * sinTheta;
    m.m[1][1] = a.y * a.y + (1 - a.y * a.y) * cosTheta;
    m.m[1][2] = a.y * a.z * (1 - cosTheta) - a.x * sinTheta;
    m.m[1][3] = 0;

    // Compute rotation of third basis vector
    m.m[2][0] = a.x * a.z * (1 - cosTheta) - a.y * sinTheta;
    m.m[2][1] = a.y * a.z * (1 - cosTheta) + a.x * sinTheta;
    m.m[2][2] = a.z * a.z + (1 - a.z * a.z) * cosTheta;
    m.m[2][3] = 0;

    return Transform(m, Transpose(m));
}

Transform LookAt(const Point3f& pos, const Point3f& look, const Vec3f& up) {
	Matrix cameraToWorld;

	Vec3f dir = Normalize(look - pos);
	Vec3f right = Normalize(Cross(Normalize(up), dir));
    Vec3f newUp = Cross(dir, right);

    cameraToWorld.m[0][0] = right.x;
    cameraToWorld.m[1][0] = right.y;
    cameraToWorld.m[2][0] = right.z;
    cameraToWorld.m[3][0] = 0.0f;

    cameraToWorld.m[0][1] = newUp.x;
    cameraToWorld.m[1][1] = newUp.y;
    cameraToWorld.m[2][1] = newUp.z;
    cameraToWorld.m[3][1] = 0.0f;

    cameraToWorld.m[0][2] = dir.x;
    cameraToWorld.m[1][2] = dir.y;
    cameraToWorld.m[2][2] = dir.z;
    cameraToWorld.m[3][2] = 0.0f;

    cameraToWorld.m[0][3] = pos.x;
    cameraToWorld.m[1][3] = pos.y;
    cameraToWorld.m[2][3] = pos.z;
    cameraToWorld.m[3][3] = 1.0f;
    
    return Transform(Inverse(cameraToWorld), cameraToWorld);
}

HEIMDALL_NAMESPACE_END