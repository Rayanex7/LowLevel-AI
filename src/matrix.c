#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>


Matrix RandomMatrix(int rows, int cols) {
    int* data = malloc(sizeof(int) * rows * cols);
    for (int i = 0; i < rows * cols; i++) {
        data[i] = rand() % 10; // Random number between 0-9
    }
    Matrix m = {data, rows, cols};
    return m;
}

int CheckMatrix(Matrix A, Matrix B) {
	if (A.cols == B.rows) return (0);
	else return (1);
}

Matrix MatrixMult(Matrix A, Matrix B) {
	if (CheckMatrix(A, B) == 1) {
		Matrix w = {NULL, 0, 0};
		return (w);
	}

	int* Mat = malloc(sizeof(int) * A.rows * B.cols);
	int x = 0, j = 0, k = 0, y = 0, z;
	int res;

	for (int i = 1 ; i <= (A.rows * B.cols) ; i++) {
		res = 0;
		j = 0;
		z = k;

		while (j < A.cols) {
			res += (A.data[j+y] * B.data[k]);
			k += B.cols;
			j++;
		}

		k = z;
		if (i % B.cols == 0) {
			y += A.cols;
			k = 0;
		}
		else k++;

		Mat[x] = res;
		x++;
	}
	Matrix w = {Mat, A.rows, B.cols};
	return (w);
}

void PrintMatrix(Matrix x) {
	if (x.data == NULL) {
		printf("invalid Matrix\n");
		return;
	}
	for (int i = 0 ; i < (x.rows * x.cols) ; i++) {
		if (i != 0 && i % x.cols == 0) printf("\n");
		printf("|%d|", x.data[i]);
	}
	printf("\n");
}

void FreeMatrix(Matrix x) {
	if (x.data != NULL) free(x.data);
}
