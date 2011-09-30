#include "GameGridParallel.h"
#include <list>
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
    list<Update> delayedUpdates;
#pragma omp parallel for shared(delayedUpdates) private(col, row)
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
            if(Grid[col][row]) //If Cell is alive
            {
                if(livingNeighbors <= 1)
                {
                    //Kill Cell
                    Update u;
                    u.updateValue = false;
                    u.position = &(Grid[col][row]);
                    delayedUpdates.push_back(u);
                }

                if(livingNeighbors >= 4)
                {
                    //Kill Cell
                    Update u;
                    u.updateValue = false;
                    u.position = &(Grid[col][row]);
                    delayedUpdates.push_back(u);
                }
                /* else remain alive */
            }
            else
            {
                if(livingNeighbors == 3)
                {
                    //ConceiveCell
                    Update u;
                    u.updateValue = true;
                    u.position = &(Grid[col][row]);
                    delayedUpdates.push_back(u);
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
