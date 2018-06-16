#ifndef DEFINES_H
#define DEFINES_H

#include <nmmintrin.h>
#include <immintrin.h>

#ifndef MATH_LIB_EXPORT
#define MATH_LIB_API __declspec(dllexport)
#else
#define MATH_LIB_API __declspec(dllimport)
#endif 

#define oX 'x'
#define oY 'y'
#define oZ 'z'
#define oW 'w'

static void* mallock_simd(size_t _size)
{
  return _aligned_malloc(_size, 16);
}

static void free_simd(void* _mem)
{
  return _aligned_free(_mem);
}


#define MulBySign(_vec1, _vec2) {                                          \
  __m128 plus = _mm_shuffle_ps((_vec1), (_vec2), _MM_SHUFFLE(0,2,0,2));    \
  __m128 minus = _mm_shuffle_ps((_vec1), (_vec2), _MM_SHUFFLE(1,3,1,3));   \
  (_vec1) = plus; (_vec2) = minus;                                         \
}

#define NanMask _mm_set_ps(1,-1, 1,-1)

#endif // ! DEFINES_H

