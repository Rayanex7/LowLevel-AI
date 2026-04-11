#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void mat_rand(int rows, int cols, Matrix *dest) {
	if (dest->rows != rows || dest->cols != cols) {printf("mat_rand(): ERROR[Dimension mismatched]\n"); return;}
	for (int i = 0; i < rows * cols; i++) {
		dest->data[i] = rand() % 10; 
	}
}

void mat_mul(Matrix A, Matrix B, Matrix *dest) {
	if (A.cols != B.rows) {printf("mat_mul(): ERROR[First matrix columns != Second matrix rows]"); return;}
	if (dest->rows != A.rows || dest->cols != B.cols) {printf("mat_mul(): ERROR[Output matrix (*dest) has different size]"); return;}
	if (dest->data == A.data || dest->data == B.data) {printf("mat_mul(): ERROR[Destination matrix cannot alias input matrices]"); return;}

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

		dest->data[x] = res;
		x++;
	}
}
/*
void mat_mul(Matrix A, Matrix B, Matrix* dest) {
	if (A.cols != B.rows) {printf("mat_mul(): ERROR[First matrix columns != Second matrix rows]"); return;}
        if (dest->rows != A.rows || dest->cols != B.cols) {printf("mat_mul(): ERROR[Output matrix (*dest) has different size]"); return;}
        if (dest->data == A.data || dest->data == B.data) {printf("mat_mul(): ERROR[Destination matrix cannot alias input matrices]"); return;}

	double res;
	int x = 0, k = 0;
	for (int i = 0 ; i < A.rows ; i++) {
		for (int j = 0 ; j < B.cols ; j++) {
			res = 0;
			for (k = 0 ; k < A.cols ; k++) {
				res += A.data[(i*A.cols)+k] * B.data[(k*B.cols)+j];
			}
			dest->data[x] = res;
			x++;
		}
	}
}*/

void mat_add(Matrix A, Matrix B, Matrix *dest)
{
	if (dest->data == A.data || dest->data == B.data) {printf("mat_mul(): ERROR[Destination matrix cannot alias input matrices]"); return;}
	if (A.rows != B.rows || A.cols != B.cols)
	{printf("mat_add(): ERROR[Dimension mismatch]"); return;}
	for (int i = 0; i < A.rows*A.cols ; i++) {dest->data[i] = A.data[i] + B.data[i];}
}

void mat_subM(Matrix A, Matrix B, Matrix *dest)
{
	if (dest->data == A.data || dest->data == B.data) {printf("mat_mul(): ERROR[Destination matrix cannot alias input matrices]"); return;}
	if (A.rows == B.rows && A.cols == B.cols) {
		for (int i = 0; i < A.rows*A.cols ; i++)
			dest->data[i] = A.data[i] - B.data[i];
	}
	else if (A.rows == B.rows && B.cols == 1) {
        	for (int i = 0; i < A.rows*A.cols ; i++) 
        	        dest->data[i] = A.data[i] - B.data[i / A.cols];
	}
	else if (A.cols == B.cols && B.rows == 1) {
                for (int i = 0; i < A.rows*A.cols ; i++)
			dest->data[i] = A.data[i] - B.data[i % B.cols];
	}
	else { printf("mat_subM: ERROR[Dimension mismatch]"); return;}
}

void mat_scale(double scalar, Matrix A, Matrix *dest) {
	for (int i = 0 ; i < A.rows*A.cols ; i++) {
		dest->data[i] = scalar * A.data[i];
	}
}

void mat_trans(Matrix A, Matrix *dest) {
	int y = 0, z = 0, a;
	for (int i = 0 ; i < A.cols ; i++) {
		a = z;
		for (int j = 0 ; j < A.rows ; j++) {
			dest->data[y] = A.data[z];
			z += A.cols;
			y++;
		}
		a++;
		z = a;
	}
}

void mat_pow(Matrix A, int power, Matrix *dest) {
	for (int i = 0 ; i < A.rows * A.cols ; i++)
		dest->data[i] = pow(A.data[i], power);
}

void mat_add_scalar(double z, Matrix A, Matrix *dest) {
        for (int i = 0; i < A.rows*A.cols ; i++)
                dest->data[i] = z + A.data[i];
}


void mat_fill(double value, Matrix *dest) {
	for (int i = 0 ; i < dest->rows*dest->cols ; i++) {dest->data[i] = value;}
}

double mat_sum(Matrix A) {
	double sum = 0;
	for (int i = 0 ; i < A.rows * A.cols ; i++) {sum += A.data[i];}
	return (sum);
}

void mat_print(Matrix m) {
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

void mat_free(Matrix x) {
	if (x.data != NULL) free(x.data);
}

void mat_sub_scalar(Matrix A, double z, Matrix *dest) {
        for (int i = 0; i < A.rows*A.cols ; i++)
                dest->data[i] = A.data[i] - z;
}

void mat_scalar_sub(double z, Matrix A, Matrix *dest) {
        for (int i = 0; i < A.rows*A.cols ; i++)
                dest->data[i] = z - A.data[i];
}

void mat_add_bias(double bias, Matrix x, Matrix *dest) {
	dest->data[0] = bias;
	for (int i = 1 ; i <= x.rows*x.cols ; i++) {
		dest->data[i] = x.data[i-1];
	}
}

Matrix mat_create(int rows, int cols) {
    Matrix m;
    m.rows = rows;
    m.cols = cols;
    m.data = malloc(sizeof(double) * rows * cols);
    return m;
}

void mat_replace(Matrix* x, Matrix* y) {
	if (x->rows != y->rows || x->cols != y->cols) {printf("mat_replace: ERROR[Dimension mismatch]"); return;}
	for (int i = 0 ; i < x->rows*x->cols ; i++) {x->data[i] = y->data[i];}
}

void mat_identity(Matrix* dest) {
	mat_fill(0, dest);
	dest->data[0] = 1;
	int index = 1;
	for (int i = dest->cols ; i < dest->rows * dest->cols ; i+=dest->cols) {
		dest->data[i+index] = 1;
		index++;
	}
}

void mat_lu(Matrix x, Matrix *L, Matrix *U) {
	double m = 0;
	mat_identity(L);
	mat_replace(U, &x);
	for (int i = 0 ; i < x.cols ; i++) {
		for (int j = i+1 ; j < x.rows ; j++) {
			m = U->data[j * x.cols + i] / U->data[i * x.cols + i];
			for (int k = i; k < x.cols ; k++) {
				U->data[j * x.cols + k] = U->data[j * x.cols + k] - m * U->data[i * x.cols + k];
			}
			L->data[j * x.cols + i] = m;
		}
	}
}

void mat_inv(Matrix x, Matrix *dest) {
	double *matL = malloc(sizeof(double)*x.rows*x.cols);
	double *matU = malloc(sizeof(double)*x.rows*x.cols);
	double *matI = malloc(sizeof(double)*x.rows*x.cols);

	f_Matrix L = {matL, x.rows, x.cols};
	f_Matrix U = {matU, x.rows, x.cols};
	f_Matrix I = {matI, x.rows, x.cols};

	mat_identity(&I);
	mat_lu(x, &L, &U);

	double* matTemp = malloc(sizeof(double)*x.rows*x.cols);
	f_Matrix temp = {matTemp, x.rows, x.cols};
	mat_fill(0, &temp);

	for (int k = 0 ; k < x.cols ; k++) {
		for (int i = 0 ; i < x.rows ; i++) {
			temp.data[i*x.cols+k] += I.data[i*x.cols+k];
			for (int j = 0 ; j < i ; j++) {
				temp.data[i*x.cols+k] -= L.data[i * x.rows + j] * temp.data[j*x.cols+k];
			}
		}
	}
	for (int k = x.rows-1 ; k >= 0 ; k--) {
		for (int i = x.rows-1 ; i >= 0 ; i--) {
			dest->data[i*x.cols+k] += temp.data[i*x.cols+k];
			for (int j = i+1 ; j < x.cols ; j++) {
				dest->data[i*x.cols+k] -= U.data[i * x.rows + j] * dest->data[j*x.cols+k];
			}
			dest->data[i*x.cols+k] /= U.data[i*x.cols+i];
		}
	}
}
