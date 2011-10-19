
/**
 * @brief Game of Life CSE 430
 *
 * @par
 * CSE 430
 * T/R 9am Section
 * Violet S. 
 *
 * @par
 * Copyright Jeremy Wright (c) 2011
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */

#include <iostream>
#include <fstream>
#include "GameGrid.h"
#include "GameGridParallelRow.h"
#include "GameGridParallelCol.h"
#include "GameGridParallel.h"
#include "RenderManager/RenderManager.h"
#include "InputGenerator.h"
#include <omp.h>
#include <time.h>
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
timespec diff(timespec start, timespec end)
{
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}
int main(int argc, const char *argv[])
{
    for(int model = 0; model < 4; model++)
    {
        ofstream fout;
        switch(model)
        {
            case 0:
                fout.open("sm_single.dat");
                break;
            case 1:
                fout.open("sm_col.dat");
                break;
            case 2:
                fout.open("sm_row.dat");
                break;
            case 3:
                fout.open("sm_full.dat");
                break;
        }
        for(int i = 10; i < 500; i += 10)
        {
            InputGenerator::Ptr ig = InputGenerator::construct();
            string filename = ig->createFile(i);
            cout << static_cast<float>(i)/static_cast<float>(500) << endl;
            GameGrid::Ptr game;
            switch(model)
            {
                case 0:
                    game = GameGrid::construct(filename, i);
                    break;
                case 1:
                    game = GameGridParallelCol::construct(filename, i);
                    break;
                case 2:
                    game = GameGridParallelRow::construct(filename, i);
                    break;
                case 3:
                    game = GameGridParallel::construct(filename, i);
                    break;
            }
            game->ParseInputFile();

            timespec startTime;
            timespec stopTime;
            fout << i;
            for(int runs = 0; runs < 5; ++runs)
            {
                clock_gettime(CLOCK_MONOTONIC, &startTime);
            size_t generations = 5;
                while(generations--)
                {
                    game->CalculateGeneration();
                }
                clock_gettime(CLOCK_MONOTONIC, &stopTime);
                timespec delta = diff(startTime, stopTime);
                fout << " " << static_cast<float>(delta.tv_nsec)*0.000001 + static_cast<float>(delta.tv_sec)*1000;
            }
            fout << endl;
        }
        fout.close();
    }
    return 0;
}
