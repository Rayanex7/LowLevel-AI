#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"

// Helper: Creates an Identity Matrix (1s on diagonal, 0s everywhere else)
Matrix CreateIdentityMatrix(int size) {
    int* data = calloc(size * size, sizeof(int)); // calloc initializes to 0
    if (data == NULL) return (Matrix){NULL, 0, 0};
    
    for (int i = 0; i < size; i++) {
        // Set the diagonal to 1
        // Formula: row * width + col
        data[i * size + i] = 1; 
    }
    Matrix m = {data, size, size};
    return m;
}

// The Truth Checker
int CompareMatrices(Matrix A, Matrix B) {
    if (A.rows != B.rows || A.cols != B.cols) return 0; // Different sizes
    
    for (int i = 0; i < A.rows * A.cols; i++) {
        if (A.data[i] != B.data[i]) {
            printf("MISMATCH at index %d: A=%d vs B=%d\n", i, A.data[i], B.data[i]);
            return 0; // False (They are different)
        }
    }
    return 1; // True (They are identical)
}

int main() {
    srand(time(NULL)); 

    printf("=== RUNNING TRUTH CHECK (Identity Test) ===\n");
    
    int SIZE = 5;

    // 1. Create a Random Matrix (The Question)
    printf("1. Generating Random Matrix A (%dx%d)...\n", SIZE, SIZE);
    Matrix A = RandomMatrix(SIZE, SIZE);
    PrintMatrix(A); // assuming you have this helper from before

    // 2. Create Identity Matrix (The Multiplier)
    printf("\n2. Generating Identity Matrix I...\n");
    Matrix I = CreateIdentityMatrix(SIZE);
    PrintMatrix(I);

    // 3. Run Your Engine
    printf("\n3. Calculating Result = A * I ...\n");
    Matrix Result = MatrixMult(A, I);
    PrintMatrix(Result);

    // 4. The Automatic Verification
    printf("\n4. Verifying...\n");
    if (CompareMatrices(A, Result) == 1) {
        printf("✅ SUCCESS: The Result matches Matrix A perfectly.\n");
        printf("   Your logic is mathematically correct.\n");
    } else {
        printf("❌ FAILURE: The math is wrong.\n");
    }

    // Cleanup
    if (A.data) free(A.data);
    if (I.data) free(I.data);
    if (Result.data) free(Result.data);

    return 0;
}
