// run.cpp : Defines the entry point for the console application.
//

#include "Matrix.h"
#include <iostream>
#include <stdio.h>
#include <ctime>

using namespace mathLib;
int main()
{
	/*size_t count = 30000000;
	Matrix3x3* mat1 = new Matrix3x3[count];
	Matrix3x3* mat2 = new Matrix3x3[count];
	
	__int64 inst = clock();
	for (size_t i = 0; i < count; i++)
	{
		mat1[i] = Matrix3x3(vector3(rand(), rand(), rand()), vector3(rand(), rand(), rand()), vector3(rand(), rand(), rand()));
		mat2[i] = Matrix3x3(vector3(rand(), rand(), rand()), vector3(rand(), rand(), rand()), vector3(rand(), rand(), rand()));
	}
	__int64 inen = clock();
	printf("initialized for %f second\n", (float)(inen - inst) / CLOCKS_PER_SEC);
	getchar();
	__int64 st = clock();
	for (size_t i = 0; i < count; i++)
	{
		mat1[i] += mat2[1];

	}
	__int64 en = clock();
	printf("CALCULATE for %f seconds\n",(float) (en - st)/CLOCKS_PER_SEC);
	getchar();
	delete[] mat1;
	delete[] mat2;*/

	size_t count = 40000000;
	float ** n = new float*[count];
	float ** v = new float*[count];


	__int64 inst = clock();
	for (size_t i = 0; i < count; i++)
	{
		n[i] = new float[4]{(float) rand(),(float)rand() ,(float)rand() ,(float)rand() };
		v[i] = new float[4]{ (float)rand(),(float)rand() ,(float)rand() ,(float)rand() };
	}
	__int64 inen = clock();
	printf("initialized for %f second\n", (float)(inen - inst) / CLOCKS_PER_SEC);
	getchar();
	__int64 st = clock();
	for (size_t i = 0; i < count; i++)
	{
		n[i][0] += v[i][0];
		n[i][1] += v[i][1];
		n[i][2] += v[i][2];
		n[i][3] += v[i][3];

	}
	__int64 en = clock();
	printf("CALCULATE for %f seconds\n", (float)(en - st) / CLOCKS_PER_SEC);
	getchar();

  return 0;
}