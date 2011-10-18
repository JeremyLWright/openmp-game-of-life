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
#include "matrix.h"

using namespace std;
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
