/**
 * @brief Matrix Multiple with an unbalalced thread load
 *
 * @par
 * Copyright Jeremy Wright (c) 2011
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */
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
#if 0 
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

void loadMatrix(int* data, Matrix A, size_t size)
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

vector<int> tokenize(string line)
{
    // construct a stream from the string
	stringstream strstr(line);

	// use stream iterators to copy the stream to the vector as whitespace separated strings
	istream_iterator<int> it(strstr);
	istream_iterator<int> end;
	vector<int> results(it, end);

	return results;
}

void parseInputFile(string filename, size_t size, Matrix& A, Matrix& B)
{
    ifstream fin(filename.c_str());
    string line;
    
    for(int row = 0; row < size && !getline(fin, line).eof(); ++row)
    {
        vector<int> values = tokenize(line);
        int col = 0;
        for(vector<int>::iterator element = values.begin();
               element != values.end();
               ++element,  ++col)
        {
            A[row][col] = *element;
        }
    }
    
    for(int row = 0; row < size && !getline(fin, line).eof(); ++row)
    {
        vector<int> values = tokenize(line);
        int col = 0;
        for(vector<int>::iterator element = values.begin();
               element != values.end();
               ++element,  ++col)
        {
            B[row][col] = *element;
        }
    }
}

void MultiplyMatrix(Matrix const A, Matrix const B, Matrix& C, size_t size)
{
    int const chunk = size%omp_get_num_threads();
#pragma omp parallel for 
    for(int i = 0; i < size; ++i)
    {
        for(int j=0; j < size; ++j)
        {
            for(int k = 0; k < size; ++k)
                C[i][j] += A[i][k] * B[k][j];
        }
    }

}

int main(int argc, const char *argv[])
{

    size_t size = atoi(argv[2]);
    Matrix A = initMatrix(size);
    Matrix B = initMatrix(size);

    parseInputFile(string(argv[1]), size, A, B);

    Matrix C = initMatrix(size);
    printMatrix(A, size);
    cout << endl << endl;
    printMatrix(B, size);

    MultiplyMatrix(A, B, C, size);
    printMatrix(C, size);

    freeMatrix(A, size);
    freeMatrix(B, size);
    freeMatrix(C, size);




    return 0;
}
