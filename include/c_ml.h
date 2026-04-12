#include "matrix.h"

#ifndef C_ML_H
#define C_ML_H

/**
 * @file c_ml.h
 * @author LYACHA Rayane
 * @date 07-03-2026
 * @brief Implementation of Machine Learning algorithmes.
 *
 * @details This library contains ML algorithms, with some other functionalities
 * that might be helpful when implementing those algorithms. This library
 * is fully written in C for high performance, the syntax might look hard
 * or annoying, but I'm doing my best to make it look easier, by making the
 * hard things under the hood, and giving the final easy to use product, while
 * maintaining the performance, and memory management.
 *
 * @note This library and documentation are written by me and not AI, so I am sorry if
 * you encounter grammatical errors or unclear explanations.
 */

/**
 * @brief struct defining the Linear Regression model
 */
typedef struct {
	Matrix x; /**< Matrix defining the training data */
	Matrix y; /**< Matrix defining the labels (output) */

	Matrix (*fit)(Matrix x, Matrix y); /**< Train the linear regression model on the input data x and target y, returning the learned weights */
	Matrix (*predict)(Matrix z, Matrix w); /**< Predict the output of x based on the weights in the matrix w */

} lr_model;

/**
 * @brief struct defining the Normalisation
 */
typedef struct {
	Matrix (*MinMax)(Matrix x); /**< Scan the training data to learn and return the minimum and maximum boundaries for each feature*/
	Matrix (*MinMaxScale)(Matrix x, Matrix min_max); /**< Applies the previous learned min/max boundaries to scale a dataset between 0 and 1*/
} Norm;

/**
 * @brief The linear regression model initializer
 *
 * @return lr_model
 */
lr_model LinearRegression();

/**
 * @brief Normalisation model initializer
 *
 * @return Norm
 */
Norm Normalisation();

/**
 * @brief Linear Regression function
 *
 * @param x The matrix containing training data
 * @param y The labels (output)
 *
 * @note A column of 1s must be added to the input matrix
 * @return Matrix Containing weights
 */
Matrix lr_fit(Matrix x, Matrix y);

/**
 * @brief Prediction function
 *
 * @param z Matrix containing data we want to predict
 * @param w Matrix containing weights resulted from lr_fit()
 */
Matrix lr_predict(Matrix z, Matrix w);

/**
 * @brief Normalisation function
 *
 * @param x Matrix to normalise
 * @param min_max Matrix containing minimal and maximal value of each column
 *
 * @return Matrix containing normalized data
 */
Matrix MMS(Matrix x, Matrix min_max);

/**
 * @brief Function that find the minimal and maximal value of each column
 *
 * @param x Matrix containing data
 * 
 * @return Matrix containing minimal and maximal value of each column of the input matrix 
 */
Matrix min_max(Matrix x);

Matrix log_fit(Matrix x, Matrix y);

double sigmoid_s(double x);

void sigmoid_m(Matrix h);

#define sigmoid(arg1) \
	_Generic((arg1), \
		Matrix: sigmoid_m, \
		double: sigmoid_s) (arg1)


#endif
