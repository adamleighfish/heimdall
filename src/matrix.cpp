#include "heimdall/matrix.h"

HEIMDALL_NAMESPACE_BEGIN

Matrix::Matrix() {
	m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.f;
	m[0][1] = m[0][2] = m[0][3] = m[1][0] = 
		m[1][2] = m[1][3] = m[2][0] = m[2][1] = 
		m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0.f;
}

Matrix::Matrix(double _m[4][4]) {
	std::memcpy(m, _m, 16 * sizeof(double));
}

Matrix::Matrix(double t00, double t01, double t02, double t03,
		double t10, double t11, double t12, double t13,
		double t20, double t21, double t22, double t23,
		double t30, double t31, double t32, double t33) {
	m[0][0] = t00;
	m[0][1] = t01;
	m[0][2] = t02;
	m[0][3] = t03;
	m[1][0] = t10;
	m[1][1] = t11;
	m[1][2] = t12;
	m[1][3] = t13;
	m[2][0] = t20;
	m[2][1] = t21;
	m[2][2] = t22;
	m[2][3] = t23;
	m[3][0] = t30;
	m[3][1] = t31;
	m[3][2] = t32;
	m[3][3] = t33;
}

bool Matrix::operator==(const Matrix& mat) const {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (m[i][j] != mat.m[i][j]) {
				return false;
			}
		}
	}
	return true;
}

bool Matrix::operator!=(const Matrix& mat) const {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (m[i][j] != mat.m[i][j]) {
				return true;
			}
		}
	}
	return false;
}

Matrix Matrix::operator*(const Matrix& mat) const {
	Matrix r;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			r.m[i][j] = m[i][0] * mat.m[0][j] + m[i][1] * mat.m[1][j] +
                        m[i][2] * mat.m[2][j] + m[i][3] * mat.m[3][j];
		}
	}
	return r;
}

Matrix Inverse(const Matrix& m) { 
	double s0 = m.m[0][0] * m.m[1][1] - m.m[1][0] * m.m[0][1];
    double s1 = m.m[0][0] * m.m[1][2] - m.m[1][0] * m.m[0][2];
    double s2 = m.m[0][0] * m.m[1][3] - m.m[1][0] * m.m[0][3];
    double s3 = m.m[0][1] * m.m[1][2] - m.m[1][1] * m.m[0][2];
    double s4 = m.m[0][1] * m.m[1][3] - m.m[1][1] * m.m[0][3];
    double s5 = m.m[0][2] * m.m[1][3] - m.m[1][2] * m.m[0][3];

    double c5 = m.m[2][2] * m.m[3][3] - m.m[3][2] * m.m[2][3];
    double c4 = m.m[2][1] * m.m[3][3] - m.m[3][1] * m.m[2][3];
    double c3 = m.m[2][1] * m.m[3][2] - m.m[3][1] * m.m[2][2];
    double c2 = m.m[2][0] * m.m[3][3] - m.m[3][0] * m.m[2][3];
    double c1 = m.m[2][0] * m.m[3][2] - m.m[3][0] * m.m[2][2];
    double c0 = m.m[2][0] * m.m[3][1] - m.m[3][0] * m.m[2][1];

    double det = 1.0 / (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);

    Matrix inv;

    inv.m[0][0] = ( m.m[1][1] * c5 - m.m[1][2] * c4 + m.m[1][3] * c3) * det;
    inv.m[0][1] = (-m.m[0][1] * c5 + m.m[0][2] * c4 - m.m[0][3] * c3) * det;
    inv.m[0][2] = ( m.m[3][1] * s5 - m.m[3][2] * s4 + m.m[3][3] * s3) * det;
    inv.m[0][3] = (-m.m[2][1] * s5 + m.m[2][2] * s4 - m.m[2][3] * s3) * det;

    inv.m[1][0] = (-m.m[1][0] * c5 + m.m[1][2] * c2 - m.m[1][3] * c1) * det;
    inv.m[1][1] = ( m.m[0][0] * c5 - m.m[0][2] * c2 + m.m[0][3] * c1) * det;
    inv.m[1][2] = (-m.m[3][0] * s5 + m.m[3][2] * s2 - m.m[3][3] * s1) * det;
    inv.m[1][3] = ( m.m[2][0] * s5 - m.m[2][2] * s2 + m.m[2][3] * s1) * det;

    inv.m[2][0] = ( m.m[1][0] * c4 - m.m[1][1] * c2 + m.m[1][3] * c0) * det;
    inv.m[2][1] = (-m.m[0][0] * c4 + m.m[0][1] * c2 - m.m[0][3] * c0) * det;
    inv.m[2][2] = ( m.m[3][0] * s4 - m.m[3][1] * s2 + m.m[3][3] * s0) * det;
    inv.m[2][3] = (-m.m[2][0] * s4 + m.m[2][1] * s2 - m.m[2][3] * s0) * det;

    inv.m[3][0] = (-m.m[1][0] * c3 + m.m[1][1] * c1 - m.m[1][2] * c0) * det;
    inv.m[3][1] = ( m.m[0][0] * c3 - m.m[0][1] * c1 + m.m[0][2] * c0) * det;
    inv.m[3][2] = (-m.m[3][0] * s3 + m.m[3][1] * s1 - m.m[3][2] * s0) * det;
    inv.m[3][3] = ( m.m[2][0] * s3 - m.m[2][1] * s1 + m.m[2][2] * s0) * det;

    return inv;
}

Matrix Transpose(const Matrix& m) {
	return Matrix(m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0],
				  m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1],
				  m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2],
				  m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3]);
}


HEIMDALL_NAMESPACE_END