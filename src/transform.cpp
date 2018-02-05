#include "heimdall/transform.h"

HEIMDALL_NAMESPACE_BEGIN

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

bool Transform::operator==(const Transform& t) const {
	return m == t.m and mInv == t.mInv;
}

bool Transform::operator!=(const Transform& t) const {
	return m != t.m or mInv != t.mInv;
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

HEIMDALL_NAMESPACE_END