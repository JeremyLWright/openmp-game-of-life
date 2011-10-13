/**
 * @brief Parallel Row version of the Game Grid
 *
 * @par
 * Copyright Jeremy Wright (c) 2011
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */
#ifndef _GAMEGRIDPARALLEL
#define _GAMEGRIDPARALLEL

#include "GameGrid.h"
#include <tr1/memory>
#include <list>
#include <string>
using namespace std;

class GameGridParallel : public GameGrid
{
    public:
        typedef std::tr1::shared_ptr<GameGridParallel> Ptr;
        typedef std::tr1::weak_ptr<GameGridParallel> WeakPtr;
        static GameGridParallel::Ptr construct(string filename, size_t size);
        virtual ~GameGridParallel();
        virtual void CalculateGeneration();
    protected:
    private:

        GameGridParallel(string filename, size_t size);
        GameGridParallel::WeakPtr self;

};

#endif /* end of include guard: _GAMEGRIDPARALLEL */
