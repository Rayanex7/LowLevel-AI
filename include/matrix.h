#ifndef	MATRIX_H
#define	MATRIX_H

#include <stdlib.h>

/**
 * @file matrix.h
 * @author LYACHA Rayane
 * @date 03-03-2026
 * @brief Implementation of Matrices, including matrix operations, and other functionnalities.
 *
 * @details This file includes functions for creating, manipulating, and freeing matrices.
 * It provides functions such as addition, multiplication, substraction, freeing, 
 * division, scaling ...
 *
 * The goal is offering a library that includes all possible matrix operations
 * and functionalities for manipulating matrices.
 * 
 * @note This library and documentation are written by me and not AI, so i am sorry if
 * you encounter grammatical errors or blur in explanation.
 */


/**
 * @brief Struct defining a single Matrix
 */
typedef struct {
	double* data; /**< Array of doubles containing all matrix elements */
	int rows; /**< Number of rows */
	int cols; /**< Number of columns */
} Matrix;

/**
 * @brief Function returning Matrix struct with random values
 *
 * @param rows Number of rows you want in this matrix
 * @param cols Number of cols you want in this matrix
 *
 * @return Matrix struct with random values with desired rows and cols
 * @note This function uses rand() function and the values generated are 
 * between 1 and 10 you can change the range of values inside the function.
 */
void mat_rand(int rows, int cols, Matrix *dest);

/**
 * @brief Add two matrices
 * 
 * @param A The first matrix 
 * @param B The second matrix
 *
 * @return Matrix The new result matrix of adding A & B
 *
 * @warning The two matrices A & B dimensions should be matched, ex: A[3,4] + B[3,4]
 */
void mat_add(Matrix A, Matrix B, Matrix *dest);

/**
 * @brief Substract two matrices
 *
 * @param A The first matrix
 * @param B The second matrix
 *
 * @return Matrix The new result matrix of substracting A & B
 *
 * @warning The two matrices A & B dimensions should be matched, ex: A[3,4] - B[3,4]
 */
void mat_subM(Matrix A, Matrix B, Matrix *dest);

/**
 * @brief Multiplication of two matrices
 *
 * @param A The first matrix
 * @param B The second matrix
 *
 * @return Matrix The new result matrix of Multiplying A & B
 *
 * @warning The number of columns of the first matrix should match 
 * the number of rows of the second matrix, ex: A[5,2] * B[2,3] -> C[5,3]
 */
void mat_mul(Matrix A, Matrix B, Matrix *dest);

/**
 * @brief Raise matrix elements to a power
 *
 * @param A The first matrix
 * @param power The number to raise for each element of the matrix
 *
 * @return Matrix The new result matrix of raising matrix A elements to power
 */
void mat_pow(Matrix A, int power, Matrix *dest);

/**
 * @brief Scalar Multiplication (Matrix Scaling)
 *
 * @param scalar The scalar to be multiplied with each element of the matrix
 * @param A The matrix which elements will be multiplied with the scalar
 *
 * @return Matrix The new result matrix of Scalar Multiplication
 */
void mat_scale(double scalar, Matrix A, Matrix *dest);

/**
 * @brief Adding a scalar to a matrix
 *
 * @param x the scalar to be added to all matrix elements
 * @param A The matrix which the scalar will be added to all its elements
 *
 * @return Matrix The new result matrix of Adding a scalar to matrix A
 */
void mat_add_scalar(double x, Matrix A, Matrix *dest);

/**
 * @brief Substracting a scalar from a matrix
 *
 * @param A The matrix
 * @param z The scalar to substract
 *
 * @return Matrix Result of A - z
 */
void mat_sub_scalar(Matrix A, double z, Matrix *dest);

/**
 * @brief Substracting each element of a matrix from a scalar
 *
 * @param z The scalar
 * @param A The matrix
 *
 * @return Matrix Result of z - A
 */
void mat_scalar_sub(double z, Matrix A, Matrix *dest);

/**
 * @brief Filling a matrix with a value
 *
 * @param value The value to be filled
 * @param rows Number of rows of this matrix
 * @param cols Number of columns of this matrix
 *
 * @return Matrix A matrix filled with a value
 */
void mat_fill(double value, Matrix *dest);

/**
 * @brief Transpose of a matrix
 *
 * @param A The matrix
 *
 * @return Matrix Transpose of A
 */
void mat_trans(Matrix A, Matrix *dest);

/**
 * @brief Adding a scalar to a matrix
 *
 * @param bias The scalar
 * @param x The matrix
 *
 * @return Matrix Result of adding the bias to the matrix
 */
void mat_add_bias(double bias, Matrix x, Matrix *dest);

/**
 * @brief The sum of all the elements in a matrix
 *
 * @param A The matrix
 *
 * @return double The sum of all elements
 */
double mat_sum(Matrix A);

/**
 * @brief Print a matrix
 *
 * @param x The matrix
 */
void mat_print(Matrix x);

/**
 * @brief Free a matrix
 *
 * @param x The matrix
 */
void mat_free(Matrix x);

/**
 * @brief Create a matrix with dynamic memory
 *
 * @param rows
 * @param cols
 *
 * @return Matrix
 */
Matrix mat_create(int rows, int cols);

/**
 * @brief Replace dynamic allocated data of x with dynamic allocated data of y
 *
 * @param x Pointer to the first matrix
 * @param y Pointer to the second matrix
 */
void mat_replace(Matrix* x, Matrix* y);

/**
 * @brief A function that does the LU decomposition of a given matrix 'x'
 *
 * @param x The input matrix to be splitted into L & U
 * @param L A pointer to an allocated matrix that will hold the L matrix
 * @param U A pointer to an allocated matrix that will hold the U matrix
 */
void mat_lu(Matrix x, Matrix *L, Matrix *U); 

/**
 * @brief Function that creates an Identity matrix
 *
 * @param x A pointer to an allocated matrix that will hold the identity matrix
 */
void mat_identity(Matrix* x);

/**
 * @brief Function that create the inverse of a matrix 
 *
 * @param X the input matrix
 * @param dest A pointer to an allocated matrix that will hold the values of the inverse matrix
 */
void mat_inv(Matrix X, Matrix *dest);

void mat_replace(Matrix* p, Matrix* x);

/**
 * @macro mat_sub(arg1, arg2)
 * 
 * @brief Type-Generic substraction macro.
 *
 * This macro uses the C11 _Generic to dispatch
 * to the correct substraction function depending
 * on the type of its two arguments.
 *
 * Supported combinations:
 * - Matrix - Matrix -> mat_sumM
 * - Matrix - double -> mat_sub_scalar
 * - double - Matrix -> mat_scalar_sub
 *
 * @param arg1 First argument
 * @param arg2 Second argument
 * @param arg3 Pointer to a Matrix
 *
 * @return Result of substraction, type depends 
 * on the two arguments.
 */
#define mat_sub(arg1, arg2, arg3) _Generic((arg1), \
	Matrix: _Generic((arg2), Matrix: mat_subM, \
				double: mat_sub_scalar), \
	double: mat_scalar_sub \
	) (arg1, arg2, arg3)

#define mat_mult(arg1, arg2, arg3) _Generic((arg1), \
		Matrix: mat_mul, \
		double: mat_scale) (arg1, arg2, arg3)

/**
 * @brief Conditional compilation for compiler-specific support
 *
 * If compiled with GCC or Clang, this block define an inline 
 * cleanup function and a macro that automatically frees Matrix 
 * memory when the variable goes out of scope. Otherwise, a warning
 * is issued and manual cleanup with mat_free() is required.
 *
 */
#if defined (__GNUC__) || defined (__clang__)

/**
 * @brief Cleanup function for Matrix.
 *
 * Automatically frees the Matrix data when used with f_Matrix macro
 *
 * @param m Pointer to the matrix to cleanup
 */
	static inline void _cleanup_matrix(Matrix* m) {
		if (m->data != NULL) {
			free(m->data);
			m->data = NULL;
		}
	}

/**
 * @macro f_Matrix 
 *
 * @brief Define a matrix variable with automatic cleanup
 *
 * When declared with f_Matrix, the variable will automatically
 * free its memory when it goes out of scopre (GCC/Clang only!).
 *
 * Example:
 * @code
 * f_Matrix x;
 * @endcode
 */
	#define f_Matrix Matrix __attribute__((cleanup(_cleanup_matrix)))

#else
	#pragma message("Warning: Compiler does not support auto-cleanup. Matrix will require manual cleanup using mat_free().")

#endif
#endif
