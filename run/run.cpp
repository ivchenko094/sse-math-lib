// run.cpp : Defines the entry point for the console application.
//

#include "Matrix.h"
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <thread>

using namespace mathLib;


void funcMatrixSSE()
{
	size_t count = 10000000;
	Matrix3x3* mat1 = new Matrix3x3[count];
	Matrix3x3* mat2 = new Matrix3x3[count];
	Matrix3x3* mat3 = new Matrix3x3[count];
	__int64 inst = clock();
	for (size_t i = 0; i < count; i++)
	{
		
		mat1[i] = Matrix3x3(vector3(rand(), rand(), rand()), vector3(rand(), rand(), rand()), vector3(rand(), rand(), rand()));
		mat2[i] = Matrix3x3(vector3(rand(), rand(), rand()), vector3(rand(), rand(), rand()), vector3(rand(), rand(), rand()));
		mat3[i] = Matrix3x3();
	}
	__int64 inen = clock();

	printf("initialized for %f second\n", (float)(inen - inst) / CLOCKS_PER_SEC);


	__int64 st = clock();
	int j = 0;
	for (size_t i = 0; i < count; i++)
	{
		mat3[i]=mat1[i] * mat2[i];

	}

	__int64 en = clock();
	printf("CALCULATE multiply matrix3x3[10000000] with SSE for %f seconds\n", (float)(en - st) / CLOCKS_PER_SEC);
	printf("%i", j);
	delete[] mat1;
	delete[] mat2;
	delete[] mat3;
}

void funcMatrix()
{
	size_t count = 10000000;
	float *** n = new float**[count];
	float *** v = new float**[count];
	float *** l = new float**[count];

	__int64 inst = clock();
	for (size_t i = 0; i < count; i++)
	{
		
		n[i] = new float*[3];
		v[i] = new float*[3];
		l[i] = new float*[3];
		for (size_t j = 0; j < 3; j++)
		{
			
			n[i][j] = new float[3]{ 1,2,1 };
			v[i][j] = new float[3]{ 1,1,1 };
			l[i][j] = new float[3]{0,0,0};
		}
		
	}
	__int64 inen = clock();

	printf("initialized for %f second\n", (float)(inen - inst) / CLOCKS_PER_SEC);


	__int64 st = clock();
	for (size_t h = 0; h < count; h++)
	{
		for ( size_t i = 0; i < 3; i++)
			for (size_t k = 0; k < 3; k++)
				for (size_t j = 0; j < 3; j++)
					l[h][i][k] += (n[h][i][j])*(v[h][j][k]);


	}

	__int64 en = clock();
	printf("CALCULATE for multiply matrix3x3[10000000] don't with SSE %f seconds\n", (float)(en - st) / CLOCKS_PER_SEC);
	for (size_t i = 0; i < count; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			
			delete[] n[i][j];
			delete[] v[i][j];
			delete[] l[i][j];
		}
		delete[] n[i];
		delete[] v[i];
		delete[] l[i];
	}
	delete[] v;
	delete[] n;
	delete[] l;
}

void funcVector() 
{
	size_t count = 40000000;
	float ** n = new float*[count];
	float ** v = new float*[count];


	__int64 inst = clock();
	for (size_t i = 0; i < count; i++)
	{
		n[i] = new float[4]{ (float)rand(),(float)rand() ,(float)rand() ,(float)rand() };
		v[i] = new float[4]{ (float)rand(),(float)rand() ,(float)rand() ,(float)rand() };
	}
	__int64 inen = clock();
	printf("initialized for %f second\n", (float)(inen - inst) / CLOCKS_PER_SEC);

	__int64 st = clock();
	for (size_t i = 0; i < count; i++)
	{
		n[i][0] *= v[i][0];
		n[i][1] *= v[i][1];
		n[i][2] *= v[i][2];
		n[i][3] *= v[i][3];

	}
	__int64 en = clock();
	printf("CALCULATE for multiply vector4[40000000] don't with SSE %f seconds\n", (float)(en - st) / CLOCKS_PER_SEC); 
	for (size_t i = 0; i < count; i++)
	{
		delete[] n[i];
		delete[] v[i];
	}
	delete[] v;
	delete[] n;
}
void funcVectorSSE()
{
	size_t count = 40000000;
	vector4* vec1= new vector4[count];
	vector4* vec2 = new vector4[count];

	__int64 inst = clock();
	for (size_t i = 0; i < count; i++)
	{
		vec1[i] = vector4 ((float)rand()/21,(float)rand() / 21,(float)rand() / 21,(float)rand() / 21);
		vec2[i] = vector4((float)rand() / 21, (float)rand() / 21, (float)rand() / 21, (float)rand() / 21);
	}
	__int64 inen = clock();
	printf("initialized for %f second\n", (float)(inen - inst) / CLOCKS_PER_SEC);


	__int64 st = clock();
	for (size_t i = 0; i < count; i++)
	{
		vec1[i] *= vec2[i];
	}
	__int64 en = clock();
	printf("CALCULATE for multiply vector4[40000000] with SSE %f seconds\n", (float)(en - st) / CLOCKS_PER_SEC);
	delete[] vec1;
	delete[] vec2;
}

int main()
{
	
	funcVector();
	
	funcVectorSSE();
	
	funcMatrix();
	
	funcMatrixSSE();
	getchar();

  return 0;
}