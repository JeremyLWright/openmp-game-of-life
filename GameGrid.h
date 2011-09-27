/**
 * @brief Game Grid for parallel game of life
 *
 * @par
 * Copyright Jeremy Wright (c) 2011
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */
#ifndef _GAMEGRID
#define _GAMEGRID

#include <tr1/memory>
#include <boost/multi_array.hpp>

class GameGrid
{
public:
    typedef std::tr1::shared_ptr<GameGrid> Ptr;
    typedef std::tr1::weak_ptr<GameGrid> WeakPtr;
    static GameGrid::Ptr construct();
    virtual ~GameGrid();
private:
    GameGrid();
    GameGrid::WeakPtr self;
    typedef boost::multi_array<bool, 2> array_type;
    typedef array_type::index index;
    array_type Grid;
    
};

#endif /* end of include guard: _GAMEGRID */
