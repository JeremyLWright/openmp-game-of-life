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
#include "RenderManager/RenderManager.h"
using std::cout;
using std::endl;


int main(int argc, const char *argv[])
{
    cout << "Welcome. Rendering World. Please Stand-by" << endl;    
    RenderManager* rm = new RenderManager();
    while(1)
    {
        if(rm->render_frame())
            break;

    }
    delete rm;
    return 0;
}
