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
}

int main(int argc, const char *argv[])
{
    if(argc != 4)
    {
        print_usage();
        exit(1);
    }

    int n;
    ifstream fin;
    n = atoi(argv[1]);
    int generations = atoi(argv[3]);
    string filename;
    if(strncmp("random", argv[2], sizeof("random")) == 0)
    {
        cout << "Using Random Configuration" << endl;
        InputGenerator::Ptr ig = InputGenerator::construct();
        filename = ig->createFile(n);
        cout << "Created: " << filename << endl;
    }

    cout << "Parsing the input file." << endl;
   // GameGrid::Ptr game = GameGrid::construct(filename, n);
    GameGrid::Ptr game = GameGridParallelRow::construct(filename, n);
//    GameGrid::Ptr game = GameGridParallel::construct(filename, n);
    game->ParseInputFile();
    cout << "Input File Complete." << endl;
#ifdef RENDER
    cout << "Welcome. Rendering World. Please Stand-by" << endl;
    RenderManager::Ptr rm = RenderManager::construct(game);
#endif 
    while(generations--)
    {
        cout << "Generation: " << generations << endl;
        game->CalculateGeneration();
#ifdef RENDER
        if(rm->render_frame())
            break;
#endif
        

    }
    return 0;
}
