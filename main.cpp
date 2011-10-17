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
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;

void print_usage()
{
    cout << "Game of Life Usage:" << endl;
    cout << "\trun-life n file" << endl;
    cout << "\t\tn := size of the n x n grid." << endl;
    cout << "\t\tfile := some file name or the keyword random." << endl;
    cout << "\t\tgenerations := Number of generations to run." << endl;
    cout << "\t\tn := Threading Model: {0: single, 1: rows, 2: col, 3: full}" << endl;
}

int main(int argc, const char *argv[])
{
    if(argc != 5)
    {
        print_usage();
        exit(1);
    }

    cout << "Threads " << omp_get_num_threads() << endl;
    int n;
    ifstream fin;
    n = atoi(argv[1]);
    int generations = atoi(argv[3]);
    string filename(argv[2]);
    if(strncmp("random", argv[2], sizeof("random")) == 0)
    {
        cout << "Using Random Configuration" << endl;
        InputGenerator::Ptr ig = InputGenerator::construct();
        filename = ig->createFile(n);
    }
        cout << "Using: " << filename << endl;

    cout << "Parsing the input file." << endl;
    GameGrid::Ptr game;
   switch(atoi(argv[4]))
   {
       case 0:
           game = GameGrid::construct(filename, n);
           cout << "Single Threaded" << endl;
           break;
       case 1:
           game = GameGridParallelRow::construct(filename, n);
           cout << "Row Model" << endl;
           break;
       case 2: 
           game = GameGridParallelCol::construct(filename, n);
           cout << "Col Model" << endl;
           break;
       case 3:
           game = GameGridParallel::construct(filename, n);
           cout << "Full Model" << endl;
           break;
       default:
           print_usage();
           exit(-1);
            break;
   }
    game->ParseInputFile();
    cout << "Input File Complete." << endl;
#ifdef RENDER
    cout << "Welcome. Rendering World. Please Stand-by" << endl;
    RenderManager::Ptr rm = RenderManager::construct(game);
#endif 
    size_t const total_generations = generations;
    int last_percent = 0;
    while(generations--)
    {
        int percent = 
            100 - static_cast<int>(static_cast<double>(generations)/static_cast<double>(total_generations)*100);
        if(percent > last_percent)
            cout << "Generation: " <<  percent << "%" << endl;
        last_percent = percent;
        game->CalculateGeneration();
#ifdef RENDER
        if(rm->render_frame())
            break;
#endif
        

    }
    return 0;
}
