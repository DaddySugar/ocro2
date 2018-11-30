#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"


//for print the Matrix
void printMatrix(Matrix mat) 
{
	for (int i = 0; i < mat.x; i++)
	{
		for (int j = 0; j < mat.y; j++)
		{
			if(mat.mat[j+i*mat.y] == 0)printf("%d ", mat.mat[j+i*mat.y]); 
			else printf(" ");
		}
		printf("\n");
	}
}

//for construct the matrix with malloc
Matrix ConstructMatrix(int x, int y) 
{
	Matrix a;
	a.x = x;
	a.y = y;
	a.mat = malloc(x * y * sizeof(int));
	return(a);
}

//init our matrix with 0
void initMatrix(Matrix a)
{
	for (int i = 0; i < a.x; i++)
	{
		for (int j = 0; j < a.y; j++)
		{
			a.mat[j + i * a.y] = 0; //like a.mat[i,j]
		}
	}
}

//sum between two matricex
Matrix sumMatrix(Matrix a, Matrix b)
{
	Matrix c = ConstructMatrix(a.x, a.y);
	initMatrix(c);
	for (int i = 0; i < a.x; i++)
	{
		for (int j = 0; j < a.y; j++)
		{
			c.mat[j + i * c.y] += a.mat[j + i * a.y] + b.mat[j + i * b.y];
		}
	}
	return(c);
}

//subtraction between two matrix
Matrix subtractionMatrix(Matrix a, Matrix b)
{
	Matrix c = ConstructMatrix(a.x, a.y);
	initMatrix(c);
	for (int i = 0; i < a.x; i++)
	{
		for (int j = 0; j < a.y; j++)
		{
			if (a.mat[j + i * a.y] - b.mat[j + i * b.y] >= 0)
				c.mat[j + i * c.y] += a.mat[j + i * a.y] - b.mat[j + i * b.y];
		}
	}
	return(c);
}

//multiplication between two matrix
Matrix multMatrix(Matrix a, Matrix b) 
{
	Matrix c = ConstructMatrix(a.x, b.y);
	initMatrix(c);
	for (int i = 0; i < a.x; i++)
	{
		for (int j = 0; j < b.y; j++)
		{
			for (int k = 0; k < b.x; k++)
			{
				c.mat[j + i * c.y] += a.mat[k + i * a.y] * b.mat[j + k * b.y];
			}		//[j,k]					//[i,k]				[k,j]
		}
	}
	return(c);
}


//give us the identity matrix
Matrix giveMatrixDiag(int x, int y)
{
	Matrix c = ConstructMatrix(x, y);
	initMatrix(c);
	for (int i = 0; i < c.x; i++)
	{
		for (int j = 0; j < c.y; j++)
		{
			if (i == j)
				c.mat[j + i * c.y] = 1;
			else
				c.mat[j + i * c.y] = 0;
		}
	}
	return c;
}

//multiplication between a matrice and an integer
Matrix multMatrixLambda(Matrix a, int lambda) 
{
	Matrix c = ConstructMatrix(a.x, a.y);
	initMatrix(c);
	for (int i = 0; i < a.x; i++)
	{
		for (int j = 0; j < a.y; j++)
		{
			c.mat[j + i * c.y] += a.mat[j + i * a.y] * lambda;
		}
	}
	return(c);
}

//sum between a matrice and an integer
Matrix sumMatrixLambda(Matrix a, int lambda)
{
	Matrix c = ConstructMatrix(a.x, a.y);
	initMatrix(c);
	for (int i = 0; i < a.x; i++)
	{
		for (int j = 0; j < a.y; j++)
		{
			c.mat[j + i * c.y] += a.mat[j + i * a.y] + lambda;
		}
	}
	return(c);
}

//subtraction between a matrice and an integer
Matrix subtractionMatrixLambda(Matrix a, int lambda) 
{
	Matrix c = ConstructMatrix(a.x, a.y);
	initMatrix(c);
	for (int i = 0; i < a.x; i++)
	{
		for (int j = 0; j < a.y; j++)
		{
			if (a.mat[j + i * a.y] - lambda >=0)
				c.mat[j + i * a.y] += a.mat[j + i * a.y] - lambda;
		}
	}
	return(c);
}


// the fonction AND for the matrix
Matrix andBinary(Matrix a, Matrix b)
{
	Matrix mat = ConstructMatrix(a.x, a.y);
	initMatrix(mat);
	if (a.x == b.x && a.y == b.y)
	{
		for (int i = 0; i < a.x; i++)
		{
			for (int j = 0; j < a.y; j++)
			{
				if (a.mat[j + i * a.y] == 0 || b.mat[j + i * b.y] == 0)
					mat.mat[j + i * mat.y] = 0;
				else
					mat.mat[j + i * mat.y] = 1;
			}
		}
	}
	return mat;
}

//give us the transposé of the matrix
Matrix transposeMatrix(Matrix a)
{
	Matrix mat = ConstructMatrix(a.y, a.x);
	initMatrix(mat);
	for (int i = 0; i < a.y; i++)
	{
		for (int j = 0; j < a.x; j++)
		{
			mat.mat[j + i * mat.y] = a.mat[i + j * a.y];
		}
	}
	return mat;
}

