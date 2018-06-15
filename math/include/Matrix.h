#ifndef MATRIX_H
#define MATRIX_H

#include "vectors.h"

namespace mathLib {

  class Matrix3x3
  {
  public:
    MATH_LIB_API Matrix3x3();
    MATH_LIB_API Matrix3x3(const __m128& _row1, const __m128& _row2, const __m128& _row3);

    MATH_LIB_API Matrix3x3(
      _In_reads_(3) const float* _row0,
      _In_reads_(3) const float* _row1,
      _In_reads_(3) const float* _row2);

    MATH_LIB_API Matrix3x3(
      const float x1, const float y1, const float z1,
      const float x2, const float y2, const float z2,
      const float x3, const float y3, const float z3);

    MATH_LIB_API Matrix3x3(const vector3& _vec0, const vector3& _vec1, const vector3& _vec2);

    MATH_LIB_API ~Matrix3x3() {};

    MATH_LIB_API friend __m128 operator * (const Matrix3x3& _mat, const vector3& _vec);
    MATH_LIB_API friend __m128 operator * (const vector3& _vec, const Matrix3x3& _mat);
    MATH_LIB_API friend Matrix3x3 operator+ (const Matrix3x3& _mat1, const Matrix3x3& _mat2);
    MATH_LIB_API friend Matrix3x3 operator- (const Matrix3x3& _mat1, const Matrix3x3& _mat2);
    MATH_LIB_API void operator += (const Matrix3x3& _mat);
    union
    {
      __declspec(align(16)) float val[3][4];
      __m128 mmval[3];
    };
  };
}
#endif // !MATRIX_H
