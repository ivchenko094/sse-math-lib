#include "Matrix.h"
#include <stdio.h>
mathLib::Matrix3x3::Matrix3x3()
{
  mmval[0] = _mm_setzero_ps();
  mmval[1] = _mm_setzero_ps();
  mmval[2] = _mm_setzero_ps();
}

mathLib::Matrix3x3::Matrix3x3(const __m128& _row0, const __m128& _row1, const __m128& _row2)
{
  mmval[0] = _row0;
  mmval[1] = _row1;
  mmval[2] = _row2;
}

mathLib::Matrix3x3::Matrix3x3(const float * _row0, const float * _row1, const float * _row2)
{
  val[0][0] = _row0[0]; val[0][1] = _row0[1]; val[0][2] = _row0[2];
  val[1][0] = _row1[0]; val[1][1] = _row1[1]; val[1][2] = _row1[2];
  val[2][0] = _row2[0]; val[2][1] = _row2[1]; val[2][2] = _row2[2];
}

mathLib::Matrix3x3::Matrix3x3(const float x1, const float y1, const float z1, 
                              const float x2, const float y2, const float z2, 
                              const float x3, const float y3, const float z3)
{
  val[0][0] = x1; val[0][1] = y1; val[0][2] = z1;
  val[1][0] = x2; val[1][1] = y2; val[1][2] = z2;
  val[2][0] = x3; val[2][1] = y3; val[2][2] = z3;
}

mathLib::Matrix3x3::Matrix3x3(const vector3 & _vec0, const vector3& _vec1, const vector3& _vec2)
{
  mmval[0] = _vec0.mmval;
  mmval[1] = _vec1.mmval;
  mmval[2] = _vec2.mmval;
}

void mathLib::Matrix3x3::operator+=(const Matrix3x3 & _mat)
{
  mmval[0] = _mm_add_ps(mmval[0], _mat.mmval[0]);
  mmval[1] = _mm_add_ps(mmval[1], _mat.mmval[1]);
  mmval[2] = _mm_add_ps(mmval[2], _mat.mmval[2]);
}

 void mathLib::Matrix3x3::operator-=(const Matrix3x3 & _mat)
{
	 mmval[0] = _mm_sub_ps(mmval[0], _mat.mmval[0]);
	 mmval[1] = _mm_sub_ps(mmval[1], _mat.mmval[1]);
	 mmval[2] = _mm_sub_ps(mmval[2], _mat.mmval[2]);
}

void mathLib::Matrix3x3::operator*=(const Matrix3x3 & _mat)
 {
	__m128 row0, row1, row2;
	__m128 rowT0 = mmval[0];
	__m128 rowT1 = mmval[1];
	__m128 rowT2 = mmval[2];
	_MM_TRANSPOSE4_PS(rowT0, rowT1, rowT2, _mm_setzero_ps());

	row0 = _mm_add_ps(
		_mm_add_ps(
			_mm_dp_ps(_mat.mmval[0], rowT0, 0x71),
			_mm_dp_ps(_mat.mmval[1], rowT0, 0x72)),
		_mm_dp_ps(_mat.mmval[2], rowT0, 0x74));

	row1 = _mm_add_ps(
		_mm_add_ps(
			_mm_dp_ps(_mat.mmval[0], rowT1, 0x71),
			_mm_dp_ps(_mat.mmval[1], rowT1, 0x72)),
		_mm_dp_ps(_mat.mmval[2], rowT1, 0x74));

	row2 = _mm_add_ps(
		_mm_add_ps(
			_mm_dp_ps(_mat.mmval[0], rowT2, 0x71),
			_mm_dp_ps(_mat.mmval[1], rowT2, 0x72)),
		_mm_dp_ps(_mat.mmval[2], rowT2, 0x74));

	_MM_TRANSPOSE4_PS(row0, row1, row2, _mm_setzero_ps());
	mmval[0] = row0;
	mmval[1] = row1;
	mmval[2] = row2;
 }

 float mathLib::Matrix3x3::Determinant() const
 {
	 __m128 Minor1 = _mm_mul_ps( 
		 _mm_shuffle_ps(mmval[1], mmval[1], _MM_SHUFFLE(1, 2, 0, 2)), 
		 _mm_shuffle_ps(mmval[2], mmval[2], _MM_SHUFFLE(2, 1, 2, 0))
	 );
	 __m128 Minor2 = _mm_mul_ps(
		 _mm_shuffle_ps(mmval[1], mmval[1], _MM_SHUFFLE(0, 1, 3, 3)),
		 _mm_shuffle_ps(mmval[2], mmval[2], _MM_SHUFFLE(1, 0, 3, 3))
	 );
	 ShuffleBySign(Minor1, Minor2);
	 __m128 maskedRow0 = _mm_mul_ps(mmval[0], NanMask);
	 Minor1 = _mm_dp_ps(Minor1, maskedRow0, 0x77);
	 Minor2 = _mm_dp_ps(Minor2, maskedRow0, 0x77);
	 return  _mm_cvtss_f32(_mm_sub_ps(Minor1, Minor2));;
 }

__m128 mathLib::operator*(const Matrix3x3 & _mat, const vector3 & _vec)
{
  __m128 result = _mm_setzero_ps();
  result = _mm_add_ps(result, _mm_dp_ps(_mat.mmval[0], _vec.mmval, 0x71));
  result = _mm_add_ps(result, _mm_dp_ps(_mat.mmval[1], _vec.mmval, 0x72));
  result = _mm_add_ps(result, _mm_dp_ps(_mat.mmval[2], _vec.mmval, 0x74));
  return result;
 
}

__m128 mathLib::operator*(const vector3 & _vec, const Matrix3x3 & _mat)
{
  __m128 x1x2x3 = _mat.mmval[0];
  __m128 y1y2y3 = _mat.mmval[1];
  __m128 z1z2z3 = _mat.mmval[2];
  __m128 result = _mm_setzero_ps();
  _MM_TRANSPOSE4_PS(x1x2x3, y1y2y3, z1z2z3, result);
  result = _mm_add_ps(result, _mm_dp_ps(_vec.mmval, x1x2x3, 0x71));
  result = _mm_add_ps(result, _mm_dp_ps(_vec.mmval, y1y2y3, 0x72));
  result = _mm_add_ps(result, _mm_dp_ps(_vec.mmval, z1z2z3, 0x74));
  return result;
}

mathLib::Matrix3x3 mathLib::operator*(const Matrix3x3 & _mat1, const Matrix3x3 & _mat2)
{    
	__m128 row0, row1, row2;
	__m128 rowT0 = _mat1.mmval[0];
	__m128 rowT1 = _mat1.mmval[1];
	__m128 rowT2 = _mat1.mmval[2];
	_MM_TRANSPOSE4_PS(rowT0, rowT1, rowT2, _mm_setzero_ps());

	row0 = _mm_add_ps( 
		_mm_add_ps(
			_mm_dp_ps(_mat2.mmval[0], rowT0, 0x71), 
			_mm_dp_ps(_mat2.mmval[1], rowT0, 0x72)),
		_mm_dp_ps(_mat2.mmval[2], rowT0, 0x74));

	row1 = _mm_add_ps(
		_mm_add_ps(
			_mm_dp_ps(_mat2.mmval[0], rowT1, 0x71),
			_mm_dp_ps(_mat2.mmval[1], rowT1, 0x72)),
		_mm_dp_ps(_mat2.mmval[2], rowT1, 0x74));

	row2 = _mm_add_ps(
		_mm_add_ps(
			_mm_dp_ps(_mat2.mmval[0], rowT2, 0x71),
			_mm_dp_ps(_mat2.mmval[1], rowT2, 0x72)),
		_mm_dp_ps(_mat2.mmval[2], rowT2, 0x74));

	_MM_TRANSPOSE4_PS(row0, row1, row2, _mm_setzero_ps());
	return Matrix3x3(row0, row1,row2);
}

mathLib::Matrix3x3 mathLib::operator+(const Matrix3x3 & _mat1, const Matrix3x3 & _mat2)
{
  __m128 row0 = _mm_add_ps(_mat1.mmval[0], _mat2.mmval[0]);
  __m128 row1 = _mm_add_ps(_mat1.mmval[1], _mat2.mmval[1]);
  __m128 row2 = _mm_add_ps(_mat1.mmval[2], _mat2.mmval[2]);
  return Matrix3x3(row0,row1,row2);
}
mathLib::Matrix3x3 mathLib::operator-(const Matrix3x3 & _mat1, const Matrix3x3 & _mat2)
{
  __m128 row0 = _mm_sub_ps(_mat1.mmval[0], _mat2.mmval[0]);
  __m128 row1 = _mm_sub_ps(_mat1.mmval[1], _mat2.mmval[1]);
  __m128 row2 = _mm_sub_ps(_mat1.mmval[2], _mat2.mmval[2]);
  return Matrix3x3(row0, row1, row2);
}