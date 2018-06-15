// run.cpp : Defines the entry point for the console application.
//

#include "Matrix.h"
#include <iostream>
#include <stdio.h>
#include <ctime>

using namespace mathLib;
int main()
{
  
  vector3 vec1(2, 2, 4);
  vector3 vec2(2, 2, 4);
  vector3 vec3(2, 2, 4);
  vector3 vec4(3, 2, 4);
  Matrix3x3 mat(vec1,vec2,vec3);

  vector3 res(mat*vec4);
  
  printf("%f, %f, %f,", res.x,res.y,res.z);
  getchar();
  return 0;
}