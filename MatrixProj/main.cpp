/**
 * @brief Matrix Multiple with an unbalalced thread load
 *
 * @par
 * Copyright Jeremy Wright (c) 2011
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef int** Matrix;

Matrix initMatrix(size_t size)
{
    Matrix M = new int*[3];
    for(int i = 0; i < 3; ++i)
       M[i] = new int[3];
    return M;
}

void printMatrix(Matrix A, size_t size)
{
    for(int i = 0; i < 3; ++i)
    {
        cout << "[";
        for(int j=0;j < 3; ++j)
        {
            cout << " " << A[i][j];
        }
        cout << " ]" << endl;
    }
}


int main(int argc, const char *argv[])
{
    Matrix A = initMatrix(3);
    Matrix B = initMatrix(3);

    Matrix C = initMatrix(3);

    for(int i = 0; i < 3; ++i)
    {
        for(int j=0;j < 3; ++j)
        {
            for(int k = 0; k < 3; ++k)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
    printMatrix(C, 3);



    return 0;
}
