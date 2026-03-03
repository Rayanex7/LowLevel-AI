#ifndef	MATRIX_H
#define	MATRIX_H

#include <stdlib.h>

typedef struct {
	int* data;
	int rows;
	int cols;
} Matrix;

Matrix RandomMatrix(int rows, int cols);

int CheckMatrix(Matrix A, Matrix B);

Matrix MatrixMult(Matrix A, Matrix B);

void PrintMatrix(Matrix x);

void FreeMatrix(Matrix x);

#endif
