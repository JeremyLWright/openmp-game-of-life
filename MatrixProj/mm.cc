#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<time.h>

int main( int argc, char **argv )
{
	int i, j, n;
	int coin;
	FILE *fp;
	time_t seed;
	char filename[ 20 ];

	// Read input parameters.

	if( argc == 3 )
	{
		n = atoi( argv[1] );
		strcpy( filename, argv[ 2 ] );

		printf( "Parameters for Matrix Multiplication: %d, and '%s'\n", n, filename );
	}
	else
	{
		printf( "Usage: input-mm n filename \n" );
		printf( "   n is the size of each matrice\n" );
		printf( "   if filename = random, write output to stdout\n" );
        printf( "   otherwise write output to filename\n" );
		exit( -1 );
	}

	// Initialize seed of random number generator

	(void) time( &seed );
	srand( (long) seed );

	if( strcmp( filename, "random" ) != 0 )
	{
		fp = fopen( filename, "w" );
		printf( "Writing two %dx%d matrices, A and B, to file %s\n", n, n, filename );
		printf( "A is upper triangular, and B is not\n" );
	}

	// First generate an n x n upper triangular matrix, A. The other entries are binary.

	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
		{
			if( j < i )
			{
				if( strcmp( filename, "random" ) == 0 )
					printf( "0 " );
				else
					fwrite( "0 ", 1, 2, fp );
			}
			else
			{	
				coin = rand() % 100;
				if(	coin <= 50 )
				{
					if( strcmp( filename, "random" ) == 0 )
						printf( "1 " );
					else
						fwrite( "1 ", 1, 2, fp );
				}
				else
				{
					if( strcmp( filename, "random" ) == 0 )
						printf( "0 " );
					else
						fwrite( "0 ", 1, 2, fp );
				}
			}
		}

		if( strcmp( filename, "random" ) == 0 )
			printf( "\n" );
		else
			fwrite( "\n", 1, 1, fp );
	}

	// Now, generate an n x n binary matrix.

	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
		{
			coin = rand() % 100;
			if(	coin <= 50 )
			{
				if( strcmp( filename, "random" ) == 0 )
					printf( "1 " );
				else
					fwrite( "1 ", 1, 2, fp );
			}
			else
			{
				if( strcmp( filename, "random" ) == 0 )
					printf( "0 " );
				else
					fwrite( "0 ", 1, 2, fp );
			}
		}

		if( strcmp( filename, "random" ) == 0 )
			printf( "\n" );
		else
			fwrite( "\n", 1, 1, fp );
	}

	if( strcmp( filename, "random" ) != 0 )
		fclose( fp );

	exit( 0 );
}
