#include <stdio.h>
#include <stdlib.h>
#include "c_ml.h"
#include "matrix.h"

lr_model LinearRegression() {
	lr_model model;

	model.fit = lr_fit;
	model.predict = lr_predict;

	return (model);
}

Norm Normalisation() {
	Norm x;
	x.MinMax = min_max;
	x.MinMaxScale = MMS;
	return (x);
}

Matrix lr_fit(Matrix x, Matrix y) {
	if (x.cols > 10000) {
		int m = x.rows;
		double alpha = 0.1;
		f_Matrix T = mat_create(x.cols, 1);
		f_Matrix x_T = mat_create(x.cols, x.rows);
		f_Matrix dot = mat_create(x.rows, T.cols);
		f_Matrix E = mat_create(x.rows, T.cols);
		f_Matrix dot1 = mat_create(x_T.rows, E.cols);
		f_Matrix G = mat_create(dot1.rows, dot1.cols);
		f_Matrix scale = mat_create(G.rows, G.cols);
		f_Matrix update = mat_create(T.rows, T.cols);

		mat_fill(0, &T); //if anything goes wrong, i have changed the mat_fill prototype
		mat_trans(x, &x_T);
	
		for (int i = 0 ; i < 1000000 ; i++) {
			mat_mul(x, T, &dot);
			mat_sub(dot, y, &E);
			mat_mul(x_T, E, &dot1);
			mat_scale((1.0/m), dot1, &G);
			mat_scale(alpha, G, &scale);
			mat_sub(T, scale, &update);
			mat_replace(&T, &update);
		}
		return (T);
	}
	else {
		double* tr = malloc(sizeof(double)*x.rows*x.cols);
		f_Matrix x_T = {tr, x.cols, x.rows};
		mat_trans(x, &x_T);

		double* t1 = malloc(sizeof(double)*x.cols*x.cols);
		f_Matrix temp1 = {t1, x.cols, x.cols};
		mat_mul(x_T, x, &temp1);

		double* inv = malloc(sizeof(double)*x.cols*x.cols);
		f_Matrix inverse = {inv, x.cols, x.cols};
		mat_inv(temp1, &inverse);

		double* t2 = malloc(sizeof(double)*x.cols*y.cols);
		f_Matrix temp2 = {t2, x.cols, y.cols};
		mat_mul(x_T, y, &temp2);

		double* t3 = malloc(sizeof(double)*x.cols*y.cols);
		Matrix temp3 = {t3, x.cols, y.cols};
		mat_mul(inverse, temp2, &temp3);
		return temp3;
	}
}

Matrix lr_predict(Matrix z, Matrix w) {
	double* Mat = malloc(sizeof(double)*z.rows*w.cols);
	Matrix preds = {Mat, z.rows, w.cols};
	mat_mul(z, w, &preds);
	return (preds);
}

Matrix min_max(Matrix x) {
	double* Mat = malloc(sizeof(double)*x.cols*2);
	double min,max;
	int y = 0;
	for (int i = 0; i < x.cols; i++) {
		min = x.data[i]; max = x.data[i];
		if (i + x.cols > x.rows*x.cols) { min = 0; max = 0; }
		for (int j = i; j < x.rows*x.cols; j+=x.cols) {
			if (x.data[j] < min) { min = x.data[j]; }
			if (x.data[j] > max) { max = x.data[j]; }
		}
		Mat[y] = min;
		Mat[y+1] = max;
		y+=2;
	}
	Matrix z = {Mat, x.cols, 2};
	return (z);
}

Matrix MMS(Matrix x, Matrix min_max) {
        double* Mat = malloc(sizeof(double) * x.rows * x.cols);
        int k = 0, y = 0;
        for (int i = 0; i < x.cols; i++) {
                for (int j = i; j < x.cols*x.rows; j+=x.cols) {
                        k = j;
                        if (min_max.data[y+1] - min_max.data[y] == 0) { Mat[k] = 0; }
                        else { Mat[k] = (x.data[j] - min_max.data[y]) / (min_max.data[y+1] - min_max.data[y]); }
                }
		y+=2;
        }
        Matrix z = {Mat, x.rows, x.cols};
        return (z);
}

void Replace(Matrix* p, Matrix* x) {
	p->rows = x->rows;
	p->cols = x->cols;
	for (int i = 0 ; i < p->rows*p->cols ; i++) {
		p->data[i] = x->data[i];
	}
}
