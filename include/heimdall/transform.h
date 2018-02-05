#pragma once

#include "heimdall/common.h"
#include "heimdall/matrix.h"
#include "heimdall/geometry.h"

HEIMDALL_NAMESPACE_BEGIN

/**
 * \brief Transformation class containing matrix representations
 */

class Transform {
  public:
  	/// Transfor public methods
  	Transform();
  	Transform(const double mat[4][4]);
  	Transform(const Matrix& _m);
  	Transform(const Matrix& _m, const Matrix& _mInv);

  	bool isIdentity() const;

  	bool operator==(const Transform& t) const;
  	bool operator!=(const Transform& t) const;

  	friend Transform Inverse(const Transform& t);
  	friend Transform Transpose(const Transform& t);

  	Transform Translate(const Vec3f& delta);
  	Transform Scale(double x, double y, double z);

  private:
  	/// Transform private data
  	Matrix m, mInv;
};

HEIMDALL_NAMESPACE_END