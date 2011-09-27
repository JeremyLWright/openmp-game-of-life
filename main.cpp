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
#include "RenderManager/RenderManager.h"
#include "InputGenerator.h"
using std::cout;
using std::endl;
using std::ifstream;


void print_usage()
{
    cout << "Game of Life Usage:" << endl;
    cout << "\trun-life n file" << endl;
    cout << "\t\tn := size of the n x n grid" << endl;
    cout << "\t\tfile := some file name or the keyword random" << endl;
}

int main(int argc, const char *argv[])
{
    if(argc != 3)
    {
        print_usage();
        exit(1);
    }

    int n;
    ifstream fin;
    n = atoi(argv[1]);
    string filename;
    if(strncmp("random", argv[2], sizeof("random")) == 0)
    {
        cout << "Using Random Configuration" << endl;
        InputGenerator::Ptr ig = InputGenerator::construct();
        filename = ig->createFile(n);
        cout << "Created: " << filename << endl;
    }

    cout << "Welcome. Rendering World. Please Stand-by" << endl;    
/*    RenderManager::Ptr rm = RenderManager::construct();
    while(1)
    {
        if(rm->render_frame())
            break;
        

    }*/
    return 0;
}
