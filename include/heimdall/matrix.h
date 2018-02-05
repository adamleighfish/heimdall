#pragma once

#include "heimdall/common.h"

HEIMDALL_NAMESPACE_BEGIN

/**
 * \brief Low-level representation of a 4x4 matrix
 */

class Matrix {
  public:
	/// Matrix public data
	float m[4][4];

	/// Matrix public method declarations
	Matrix();
	Matrix(float _m[4][4]);
	Matrix(float t00, float t01, float t02, float t03,
			float t10, float t11, float t12, float t13,
			float t20, float t21, float t22, float t23,
			float t30, float t31, float t32, float t33);

	bool operator==(const Matrix& mat) const;
	bool operator!=(const Matrix& mat) const;
	Matrix operator*(const Matrix& mat) const;
};

Matrix Inverse(const Matrix& m);
Matrix Transpose(const Matrix& m);

HEIMDALL_NAMESPACE_END