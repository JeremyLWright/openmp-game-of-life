/**
 * @brief Parallel Row version of the Game Grid
 *
 * @par
 * Copyright Jeremy Wright (c) 2011
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */
#ifndef _GAMEGRIDPARALLELCOL
#define _GAMEGRIDPARALLELCOL

#include "GameGrid.h"
#include <tr1/memory>
#include <list>
#include <string>
using namespace std;

class GameGridParallelCol : public GameGrid
{
    public:
        typedef std::tr1::shared_ptr<GameGridParallelCol> Ptr;
        typedef std::tr1::weak_ptr<GameGridParallelCol> WeakPtr;
        static GameGridParallelCol::Ptr construct(string filename, size_t size);
        virtual ~GameGridParallelCol();
        virtual void CalculateGeneration();
    protected:
    private:

        GameGridParallelCol(string filename, size_t size);
        GameGridParallelCol::WeakPtr self;

};

#endif /* end of include guard: _GAMEGRIDPARALLELCOL */
