#ifndef VECTORS_H
#define VECTORS_h

#include "Defines.h"
namespace mathLib {

  class vector4
  {
  public:
    MATH_LIB_API vector4() :mmval(_mm_setzero_ps()) {};
    MATH_LIB_API virtual ~vector4() {};

    MATH_LIB_API vector4(
      const float _x,
      const float _y,
      const float _z,
      const float _w
    ): x(_x), y(_y), z(_z), w(_w) {}

    MATH_LIB_API vector4(const __m128& _vec) : mmval(_vec) {}
    MATH_LIB_API vector4(_In_reads_(4) const float* _vec)
      : x(_vec[0]), y(_vec[1]), z(_vec[2]), w(_vec[3]) {}

    MATH_LIB_API __forceinline __m128 operator + (const vector4& _vec2) const;
    MATH_LIB_API __forceinline __m128 operator - (const vector4& _vec2) const;
    MATH_LIB_API __forceinline __m128 operator * (const vector4& _vec2) const;
    MATH_LIB_API __forceinline __m128 operator / (const vector4& _vec2) const;
    MATH_LIB_API __forceinline void operator += (const vector4& _vec);
    MATH_LIB_API __forceinline void operator -= (const vector4& _vec);
    MATH_LIB_API __forceinline void operator *= (const vector4& _vec);
    MATH_LIB_API __forceinline void operator /= (const vector4& _vec);
    MATH_LIB_API __forceinline bool operator == (const vector4 & _vec) const;
    MATH_LIB_API __forceinline bool operator != (const vector4 & _vec) const;
    MATH_LIB_API __forceinline void operator = (const vector4 & _vec);
    MATH_LIB_API __forceinline void operator = (const __m128&  _mmval);
    MATH_LIB_API __forceinline float operator [] (const char ch) const;
    MATH_LIB_API __forceinline float operator [] (const size_t i) const;

    MATH_LIB_API __forceinline void* operator new[](unsigned __int64 _size);
    MATH_LIB_API __forceinline void operator delete[](void* p);
    MATH_LIB_API __forceinline vector4 Normalize() const;
    MATH_LIB_API __forceinline float DotProduct(const vector4 & _vec) const;
    MATH_LIB_API __forceinline float Length() const;
    MATH_LIB_API __forceinline float RLength() const; // 1\Length
    
    union
    {
    __declspec(align(16)) struct
      {
        float x;
        float y;
        float z;
        float w;
      };
      __declspec(align(16)) __m128 mmval;
      __declspec(align(16)) float M[4];
    };
  };

  class vector3
  {
  public:
    MATH_LIB_API vector3() :mmval(_mm_setzero_ps()) {};
    MATH_LIB_API virtual ~vector3() {};

    MATH_LIB_API vector3(_In_reads_(3)const float* _vec) :
      x(_vec[0]), y(_vec[1]), z(_vec[2]) {};

    MATH_LIB_API vector3(
      const float _x,
      const float _y,
      const float _z
    ) : x(_x), y(_y), z(_z) {};

    MATH_LIB_API vector3(__m128 _mmval) :mmval(_mmval) {};
       
    union 
    {
      __declspec(align(16))struct
      {
        float x, y, z;
      };
      __declspec(align(16)) float val[3];
      __declspec(align(16))__m128 mmval;
    };

    MATH_LIB_API __forceinline friend __m128 operator + (const vector3& _vec1, const vector3& _vec2);
    MATH_LIB_API __forceinline friend __m128 operator - (const vector3& _vec1, const vector3& _vec2);
    MATH_LIB_API __forceinline friend __m128 operator * (const vector3& _vec1, const vector3& _vec2);
    MATH_LIB_API __forceinline friend __m128 operator / (const vector3& _vec1, const vector3& _vec2);
    MATH_LIB_API __forceinline void operator += (const vector3& _vec);
    MATH_LIB_API __forceinline void operator -= (const vector3& _vec);
    MATH_LIB_API __forceinline void operator *= (const vector3& _vec);
    MATH_LIB_API __forceinline void operator /= (const vector3& _vec);

    MATH_LIB_API __forceinline void operator = (const __m128& _mmval);
    MATH_LIB_API __forceinline void operator = (const vector3& _vec);
	  MATH_LIB_API __forceinline bool operator == (const vector3& _vec) const;
	  MATH_LIB_API __forceinline bool operator != (const vector3& _vec) const;
    MATH_LIB_API __forceinline vector3 Normalize() const;
    MATH_LIB_API __forceinline float Length() const;
    MATH_LIB_API __forceinline float RLength() const;
    MATH_LIB_API __forceinline __m128 Cross(vector3& _vec) const;
    
    MATH_LIB_API __forceinline float DotProduct(const vector3 & _vec) const;
  };

}
#endif