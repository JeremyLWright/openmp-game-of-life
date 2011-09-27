#include "InputGenerator.h"
extern "C" {
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
}

InputGenerator::Ptr InputGenerator::construct()
{
    InputGenerator::Ptr c(new InputGenerator());
    c->self = c;
    return c;
}


InputGenerator::InputGenerator() {}
InputGenerator::~InputGenerator() {}

string InputGenerator::createFile(size_t n)
{
    time_t seed;
	time( &seed );
	srand( seed );
    char filename[L_tmpnam];
    tmpnam(filename);
	FILE* fp = fopen( filename, "w" );
	// Iterate and generate n x n board.

	for( size_t i = 0; i < n; i++ )
	{
		for( size_t j = 0; j < n; j++ )
		{
			int coin = rand() % 100;
			if(	coin <= 40 )
			{
				fwrite( "1 ", sizeof(char), sizeof("1 "), fp );
			}
			else
			{
				fwrite( "0 ", sizeof(char), sizeof("0 "), fp );
			}
		}

		fwrite( "\n", 1, 1, fp );
	}

	fclose( fp );
    string f(filename);
    return f;
}

