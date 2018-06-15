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


#endif // ! DEFINES_H

