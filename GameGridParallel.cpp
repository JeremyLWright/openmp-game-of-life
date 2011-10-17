#include "GameGridParallel.h"
#include <list>
extern "C" {
#include <omp.h>
}
using namespace std;

GameGridParallel::Ptr GameGridParallel::construct(string filename, size_t size)
{
    GameGridParallel::Ptr c(new GameGridParallel(filename, size));
    c->self = c;
    return c;
}

GameGridParallel::GameGridParallel(string filename, size_t size)
    : GameGrid(filename, size)
{

}

GameGridParallel::~GameGridParallel()
{
}

void GameGridParallel::CalculateGeneration()
{
    vector<Update> delayedUpdates[omp_get_max_threads()];
#pragma omp parallel for
    for(int i = 0; i < omp_get_max_threads(); i++)
        delayedUpdates[i].reserve(GetGridSize());

#pragma omp parallel for
   for(size_t row = 0; row < GetGridSize(); ++row)
    {
        for(size_t col = 0; col < GetGridSize(); ++col)
        {
            uint32_t livingNeighbors = CountLivingNeighbors(col, row);
#ifdef DEBUG
            cout << "Row: " << row 
                << "Col: " << col
                << ": " << livingNeighbors << endl;
#endif
            Update u;
            u.threadId = omp_get_thread_num();
            u.position = &(Grid[col][row]);
            u.threadPosition = &(GridThreads[col][row]);
            if(Grid[col][row]) //If Cell is alive
            {
                if(livingNeighbors <= 1)
                {
                    //Kill Cell
                    u.updateValue = false;
                    delayedUpdates[u.threadId].push_back(u);
                }

                if(livingNeighbors >= 4)
                {
                    //Kill Cell
                    u.updateValue = false;
                    delayedUpdates[u.threadId].push_back(u);
                }
                /* else remain alive */
            }
            else
            {
                if(livingNeighbors == 3)
                {
                    //ConceiveCell
                    u.updateValue = true;
                    delayedUpdates[u.threadId].push_back(u);
                }
            }

        }
    }  // Commit all updates to the grid.
   for(int t = 0; t < omp_get_max_threads() ; ++t)
    for(vector<Update>::const_iterator i = delayedUpdates[t].begin();
            i != delayedUpdates[t].end();
            ++i)
    {
        *(i->position) = i->updateValue;
        *(i->threadPosition) = i->threadId;
    }

}
