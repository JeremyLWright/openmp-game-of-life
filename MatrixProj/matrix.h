#ifndef _MATRIX
#define _MATRIX

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <string.h>
#include <omp.h>

using namespace std;

typedef int** Matrix;


Matrix initMatrix(size_t size);
void freeMatrix(Matrix A, size_t size);
void printMatrix(Matrix A, size_t size);
void loadMatrix(int* data, Matrix A, size_t size);
void MultiplyMatrix(Matrix const A, Matrix const B, Matrix& C, size_t size);
#endif /* end of include guard: _MATRIX */
