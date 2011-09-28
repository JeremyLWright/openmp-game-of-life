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
#include <vector>
#include <string>

using std::string;
using std::vector;

class GameGrid
{
public:
    typedef std::tr1::shared_ptr<GameGrid> Ptr;
    typedef std::tr1::weak_ptr<GameGrid> WeakPtr;
    static GameGrid::Ptr construct(string filename, size_t size);
    virtual ~GameGrid();
    virtual void ParseInputFile();
protected:
    virtual vector<string> tokenize(string);
    bool** Grid;
private:
    GameGrid(string filename, size_t size);
    string filename;
    GameGrid::WeakPtr self;
    
};

#endif /* end of include guard: _GAMEGRID */
