#pragma once

#include "heimdall/common.h"

HEIMDALL_NAMESPACE_BEGIN

/**
 * \brief Low-level representation of a 4x4 matrix
 */

class Matrix {
  public:
	/// Matrix public data
	double m[4][4];

	/// Matrix public method declarations
	Matrix();

	Matrix(double _m[4][4]);

	Matrix(double t00, double t01, double t02, double t03,
			double t10, double t11, double t12, double t13,
			double t20, double t21, double t22, double t23,
			double t30, double t31, double t32, double t33);

	bool operator==(const Matrix& mat) const;

	bool operator!=(const Matrix& mat) const;

	Matrix operator*(const Matrix& mat) const;
};

Matrix Inverse(const Matrix& m);
Matrix Transpose(const Matrix& m);

HEIMDALL_NAMESPACE_END