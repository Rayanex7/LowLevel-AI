#ifndef	MATRIX_H
#define	MATRIX_H

#include <stdlib.h>

typedef struct {
	double* data;
	int rows;
	int cols;
} Matrix;

Matrix RandomMatrix(int rows, int cols);

Matrix MatrixAdd(Matrix A, Matrix B);

Matrix MatrixSub(Matrix A, Matrix B);

Matrix Transpose(Matrix A);

Matrix MatrixMult(Matrix A, Matrix B);

Matrix MatrixScale(double scalar, Matrix A);

Matrix MatrixPower(Matrix A, int power);

Matrix MatrixScaleAdd(double x, Matrix A);

double MatrixSum(Matrix A);

int CheckMatrix(Matrix A, Matrix B);

void PrintMatrix(Matrix x);

void FreeMatrix(Matrix x);

#endif
