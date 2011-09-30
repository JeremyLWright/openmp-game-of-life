/**
 * @brief Parallel Row version of the Game Grid
 *
 * @par
 * Copyright Jeremy Wright (c) 2011
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */
#ifndef _GAMEGRIDPARALLELROW
#define _GAMEGRIDPARALLELROW

#include "GameGrid.h"
#include <tr1/memory>
#include <list>
#include <string>
using namespace std;

class GameGridParallelRow : public GameGrid
{
    public:
        typedef std::tr1::shared_ptr<GameGridParallelRow> Ptr;
        typedef std::tr1::weak_ptr<GameGridParallelRow> WeakPtr;
        static GameGridParallelRow::Ptr construct(string filename, size_t size);
        virtual ~GameGridParallelRow();
        virtual void CalculateGeneration();
    protected:
    private:

        GameGridParallelRow(string filename, size_t size);
        GameGridParallelRow::WeakPtr self;

};

#endif /* end of include guard: _GAMEGRIDPARALLELROW */
