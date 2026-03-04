#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


Matrix RandomMatrix(int rows, int cols) {
    double* data = malloc(sizeof(double) * rows * cols);
    for (int i = 0; i < rows * cols; i++) {
        data[i] = rand() % 10; 
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

	double* Mat = malloc(sizeof(double) * A.rows * B.cols);
	int x = 0, j = 0, k = 0, y = 0, z;
	double res;

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

Matrix MatrixAdd(Matrix A, Matrix B)
{
	if (A.rows != B.rows || A.cols != B.cols)
	{
		Matrix x = {NULL, 0, 0};
		return (x);
	}
	double* Mat = malloc(sizeof(double)*A.rows*A.cols);
	for (int i = 0; i < A.rows*A.cols ; i++)
		Mat[i] = A.data[i] + B.data[i];
	Matrix x = {Mat, A.rows, A.cols};
	return (x);
}

Matrix MatrixSub(Matrix A, Matrix B)
{
	if (A.rows != B.rows || A.cols != B.cols)
	{
		Matrix x = {NULL, 0, 0};
		return (x);
	}
	double* Mat = malloc(sizeof(double)*A.rows*A.cols);
	for (int i = 0; i < A.rows*A.cols ; i++)
		Mat[i] = A.data[i] - B.data[i];
	Matrix x = {Mat, A.rows, A.cols};
	return (x);
}

Matrix MatrixScale(double scalar, Matrix A) {
	double* Mat = malloc(sizeof(double)*A.rows*A.cols);
	for (int i = 0 ; i < A.rows*A.cols ; i++) {
		Mat[i] = scalar * A.data[i];
	}
	Matrix x = {Mat, A.rows, A.cols};
	return (x);
}

Matrix Transpose(Matrix A) {
	double* Mat = malloc(sizeof(double) * A.rows * A.cols);
	int y = 0, z = 0, a;
	for (int i = 0 ; i < A.cols ; i++) {
		a = z;
		for (int j = 0 ; j < A.rows ; j++) {
			Mat[y] = A.data[z];
			z += A.cols;
			y++;
		}
		a++;
		z = a;
	}
	Matrix x = {Mat, A.cols, A.rows};
	return (x);
}

double MatrixSum(Matrix A) {
	double sum = 0;
	for (int i = 0 ; i < A.rows * A.cols ; i++) {sum += A.data[i];}
	return (sum);
}

Matrix MatrixPower(Matrix A, int power) {
	double* Mat = malloc(sizeof(double) * A.rows * A.cols);
	for (int i = 0 ; i < A.rows * A.cols ; i++)
		Mat[i] = pow(A.data[i], power);
	Matrix x = {Mat, A.rows, A.cols};
	return (x);
}

void PrintMatrix(Matrix m) {
    if (m.data == NULL) {
        printf("Invalid Matrix (NULL)\n");
        return;
    }

    printf("Matrix (%dx%d):\n", m.rows, m.cols);
    
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            double val = m.data[i * m.cols + j];
            
            if ((int)val == val) {
                printf("%-6.0f", val); 
            } else {
                printf("%-6.2f", val); 
            }
        }
        printf("\n"); 
    }
    printf("\n");
}

Matrix MatrixScaleAdd(double z, Matrix A) {
        double* Mat = malloc(sizeof(double)*A.rows*A.cols);
        for (int i = 0; i < A.rows*A.cols ; i++)
                Mat[i] = z + A.data[i];
        Matrix x = {Mat, A.rows, A.cols};
        return (x);

}

void FreeMatrix(Matrix x) {
	if (x.data != NULL) free(x.data);
}
