#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include "matrix.h"


int main() {
	double X[] = {1,2,3,4,5};
	double Y[] = {2,4,6,8,10};

	Matrix x = {X, 1, 5};
	Matrix y = {Y, 1, 5};
	
	double theta_0 = 0;
	double theta_1 = 0;
	double alpha = 0.01;
	int m = x.cols;
	Matrix x_T = Transpose(x);

	int epochs = 10000000;

	for (int i = 0 ; i < epochs ; i++) {
		Matrix scalar = MatrixScale(theta_1, x); 
		Matrix h_theta = MatrixScaleAdd(theta_0, scalar);
		Matrix errors = MatrixSub(h_theta, y);

		double d_theta_0 = (1.0/m) * MatrixSum(errors);
		Matrix dot = MatrixMult(errors, x_T);
		double d_theta_1 = (1.0/m) * MatrixSum(dot);

		theta_0 -= alpha * d_theta_0;
		theta_1 -= alpha * d_theta_1;

		if (i % 1000 == 0) {
			Matrix sq_err = MatrixPower(errors, 2);
			double cost = (1.0/(2*m)) * MatrixSum(sq_err);
			printf("Theta_0: %.40f | Theta_1: %.40f | Cost = %.40f\n", theta_0, theta_1, cost);
			FreeMatrix(sq_err);
		}
		FreeMatrix(scalar);
		FreeMatrix(h_theta);
		FreeMatrix(errors);
		FreeMatrix(dot);
	}
	FreeMatrix(x_T);
	printf("Optimised Parameters: Theta_0: %.40f | Theta_1: %.40f |\n", theta_0, theta_1);
	return (0);
}
