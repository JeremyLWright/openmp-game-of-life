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
#include <stdint.h>
#include <list>
using std::list;
using std::string;
using std::vector;

class GameGrid
{
public:
    typedef std::tr1::shared_ptr<GameGrid> Ptr;
    typedef std::tr1::weak_ptr<GameGrid> WeakPtr;
    enum Direction{UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT} ;
    static GameGrid::Ptr construct(string filename, size_t size);
    virtual ~GameGrid();
    virtual void ParseInputFile();
    virtual void CalculateGeneration();
    virtual bool GetCellValue(size_t col, size_t row);
    virtual int GetThreadValue(size_t col, size_t row);
    virtual size_t GetGridSize();
protected:
    struct Update {
        bool updateValue;
        bool* position;
        int* threadPosition;
        int threadId;
    };
    virtual void commitUpdates(list<Update> const & updates);
    virtual vector<bool> tokenize(string);
    bool MovePtr(bool** cellPtr, Direction direction, size_t col, size_t row);
    uint32_t CountLivingNeighbors(size_t col, size_t row);
    bool** Grid;
    int** GridThreads;
    size_t gridSize;
    string filename;
    GameGrid(string filename, size_t size);
private:
    GameGrid::WeakPtr self;
    
};

#endif /* end of include guard: _GAMEGRID */
