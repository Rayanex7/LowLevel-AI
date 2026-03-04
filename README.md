# LowLevelAI: Machine Learning from Scratch in C

A lightweight, low-level linear algebra library and machine learning implementation written in pure C (Standard C99).

## 🚀 Features
* **Matrix Operations:** Multiplication, Transpose, Scaling, Addition/Subtraction.
* **Memory Management:** Manual allocation and cleanup utils.
* **Algorithms:** Linear Regression with Gradient Descent.

## 📂 Project Structure
* `src/matrix.c`: Core implementation of matrix math.
* `examples/linear_regression.c`: a model training y = 2x.

## 🛠️ How to Run
Compile the linear regression example using GCC:

```bash
gcc -O3 -I./include src/matrix.c examples/linear_regression.c -o train_model -lm
./train_model
