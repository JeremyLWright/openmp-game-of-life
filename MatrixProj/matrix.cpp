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

Matrix initMatrix(size_t size)
{
    Matrix M = new int*[size];
    for(int i = 0; i < size; ++i)
    {
       M[i] = new int[size];
       memset(M[i], 0, sizeof(int)*size);
    }
    return M;
}

void freeMatrix(Matrix A, size_t size)
{

}

void printMatrix(Matrix A, size_t size)
{
#if 1 
    for(int i = 0; i < size; ++i)
    {
        cout << "[";
        for(int j=0;j < size; ++j)
        {
            cout << " " << A[i][j];
        }
        cout << " ]" << endl;
    }
#endif
}

void loadMatrix(int* data, Matrix& A, size_t size)
{
    int k = 0;
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            A[i][j] = data[k++];
        }
    }
}

void MultiplyMatrix(Matrix const A, Matrix const B, Matrix& C, size_t size)
{
    int const chunk = size%omp_get_num_threads();
    omp_set_num_threads(12);
#pragma omp parallel for schedule(dynamic, chunk)
   for(int i = 0; i < size; ++i)
    {
        for(int j=0; j < size; ++j)
        {
            for(int k = 0; k < size; ++k)
                C[i][j] += A[i][k] * B[k][j];
        }
    }

}


