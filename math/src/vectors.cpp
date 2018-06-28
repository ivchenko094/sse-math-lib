#include "vectors.h"

__m128 mathLib::vector4::operator+(const vector4& _vec2) const
{
  return _mm_add_ps(mmval, _vec2.mmval);
}

__m128 mathLib::vector4::operator-(const vector4& _vec2) const
{
  return _mm_sub_ps(mmval, _vec2.mmval);
}

__m128 mathLib::vector4::operator*( const vector4& _vec2) const
{
  return _mm_mul_ps(mmval, _vec2.mmval);
}

__m128 mathLib::vector4::operator/(const vector4& _vec2) const
{
  return _mm_div_ps(mmval, _vec2.mmval);
}

void mathLib::vector4::operator+=(const vector4& _vec) 
{
  mmval = _mm_add_ps(mmval, _vec.mmval);
}

void mathLib::vector4::operator-=(const vector4& _vec)
{
  mmval = _mm_sub_ps(mmval, _vec.mmval);
}

void mathLib::vector4::operator*=(const vector4& _vec)
{
  mmval = _mm_mul_ps(mmval, _vec.mmval);

}

void mathLib::vector4::operator/=(const vector4& _vec)
{
  mmval = _mm_div_ps(mmval, _vec.mmval);
}

bool mathLib::vector4::operator==(const vector4 & _vec) const
{
  return (((_mm_movemask_ps(_mm_cmpeq_ps(mmval, _vec.mmval))) & 0x7) == 0x7);
}

bool mathLib::vector4::operator!=(const vector4 & _vec) const
{
  return !(*this == _vec);
}

void mathLib::vector4::operator=(const vector4 & _vec)
{
  mmval = _vec.mmval;
}

void mathLib::vector4::operator=(const __m128& _mmval)
{
  mmval = _mmval;
}

float mathLib::vector4::operator[](const char ch) const
{
  return (ch == 'x') ? x :( (ch == 'y') ? y :(ch == 'z') ? z : w );
}

float mathLib::vector4::operator[](const size_t i) const
{
  return (i == 1) ? x : ((i == 2) ? y : (i == 3) ? z : w);
}

void * mathLib::vector4::operator new[](unsigned __int64 _size)
{
  return mallock_simd(_size);
}

void mathLib::vector4::operator delete[](void * p)
{
  return free_simd(p);
}


mathLib::vector4 mathLib::vector4::Normalize() const
{
  return _mm_div_ps(mmval, _mm_sqrt_ps(_mm_dp_ps(mmval,mmval, 0xFF)));
}

 float mathLib::vector4::DotProduct(const vector4 & _vec) const
{
  return _mm_cvtss_f32(_mm_dp_ps(mmval, _vec.mmval, 0xF1));
}

float mathLib::vector4::Length() const
 {
   return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(mmval, mmval, 0xF1)));
 }

float mathLib::vector4::RLength() const
{
  return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_dp_ps(mmval, mmval, 0xF1)));
}

 __m128 mathLib::operator+(const vector3& _vec1, const vector3& _vec2)
{
   return  _mm_add_ps(_vec1.mmval, _vec2.mmval);
}

 __m128 mathLib::operator-(const vector3& _vec1, const vector3& _vec2)
 {
   return _mm_sub_ps(_vec1.mmval, _vec2.mmval);
 }

 __m128 mathLib::operator*(const vector3& _vec1, const vector3& _vec2)
 {
   return _mm_mul_ps(_vec1.mmval, _vec2.mmval);
 }

 __m128 mathLib::operator/(const vector3& _vec1, const vector3& _vec2)
 {
   return _mm_div_ps(_vec1.mmval, _vec2.mmval);
 }

 void mathLib::vector3::operator+=(const vector3 & _vec)
 {
   mmval = _mm_add_ps(mmval, _vec.mmval);
 }

 void mathLib::vector3::operator-=(const vector3 & _vec)
 {
   mmval = _mm_sub_ps(mmval, _vec.mmval);
 }

 void mathLib::vector3::operator*=(const vector3 & _vec)
 {
   mmval = _mm_mul_ps(mmval, _vec.mmval);
 }

 void mathLib::vector3::operator/=(const vector3 & _vec)
 {
   mmval = _mm_div_ps(mmval, _vec.mmval);
 }

 void mathLib::vector3::operator=(const __m128& _mmval)
 {
  mmval = _mmval;
 }

void mathLib::vector3::operator=(const vector3 & _vec)
{
  mmval = _vec.mmval ;
}

bool mathLib::vector3::operator==(const vector3 & _vec) const
{
  return (((_mm_movemask_ps(_mm_cmpeq_ps(mmval, _vec.mmval))) & 0x7) == 0x7);
}

bool mathLib::vector3::operator!=(const vector3 & _vec) const
{
	return !(*this == _vec);
}

mathLib::vector3 mathLib::vector3::Normalize() const
{
  return _mm_div_ps(mmval, _mm_sqrt_ps(_mm_dp_ps(mmval, mmval, 0x77)));
}

float mathLib::vector3::Length() const
{
  return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(mmval,mmval,0x71)));
}

float mathLib::vector3::RLength() const
{
  return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_dp_ps(mmval, mmval, 0x71)));
}

__m128 mathLib::vector3::Cross(vector3 & _vec) const
{
  return _mm_div_ps(
    _mm_mul_ps(_mm_shuffle_ps(mmval, mmval, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(_vec.mmval, _vec.mmval, _MM_SHUFFLE(3, 1, 0, 2))),
    _mm_mul_ps(_mm_shuffle_ps(mmval, mmval, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(_vec.mmval, _vec.mmval, _MM_SHUFFLE(3, 0, 2, 1)))
  );
}

float mathLib::vector3::DotProduct(const vector3 & _vec) const
{
 ;
  return _mm_cvtss_f32(_mm_dp_ps(mmval, _vec.mmval, 0x71));
  
}
