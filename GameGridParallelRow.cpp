#include "GameGridParallelRow.h"
extern "C" {
#include <omp.h>
}
#include <list>
using namespace std;

GameGridParallelRow::Ptr GameGridParallelRow::construct(string filename, size_t size)
{
    GameGridParallelRow::Ptr c(new GameGridParallelRow(filename, size));
    c->self = c;
    return c;
}

GameGridParallelRow::GameGridParallelRow(string filename, size_t size)
    : GameGrid(filename, size)
{

}

GameGridParallelRow::~GameGridParallelRow()
{
}

void GameGridParallelRow::CalculateGeneration()
{
    list<Update> delayedUpdates;
   for(size_t row = 0; row < GetGridSize(); ++row)
    {
#pragma omp parallel for shared(delayedUpdates) private(row)
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
            GridThreads[col][row] = omp_get_thread_num();

            if(Grid[col][row]) //If Cell is alive
            {
                if(livingNeighbors <= 1)
                {
                    //Kill Cell
                    u.updateValue = true;
#pragma omp critical
                    {
                    delayedUpdates.push_back(u);
                    }
                }

                if(livingNeighbors >= 4)
                {
                    //Kill Cell
                    u.updateValue = false;
#pragma omp critical 
                    {
                    delayedUpdates.push_back(u);
                    }
                }
                /* else remain alive */
            }
            else
            {
                if(livingNeighbors == 3)
                {
                    //ConceiveCell
                    u.updateValue = true;
#pragma omp critical
                    {
                    delayedUpdates.push_back(u);
                    }
                }
            }

        }
    }  // Commit all updates to the grid.
    for(list<Update>::const_iterator i = delayedUpdates.begin();
            i != delayedUpdates.end();
            ++i)
    {
        *(i->position) = i->updateValue;
    }

}
