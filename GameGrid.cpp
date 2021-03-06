#include "GameGrid.h"
#include <cstring>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <list>
#include <omp.h>
using std::list;
using std::cout;
using std::endl;
using std::ifstream;
using std::istream_iterator;
using std::stringstream;
using std::copy;
namespace {
    /**
	 * Uses a C++ streams to convert a string representation to some other type.
	 *
	 * @param[out] t Target to save the converted value
	 * @param[in] s Source string to convert the value from.
	 * @param[in] f Format e.g.std::hex, or std::dec
	 * @return returns fail is conversion is not successful.
	 */
	template <typename T>
	bool from_string(T& t, const std::string& s, std::ios_base& (*f)(std::ios_base&))
	{
		std::istringstream iss(s, std::istringstream::in);
		return !(iss >> f >> t).fail();
	}
    
}

GameGrid::Ptr GameGrid::construct(string filename, size_t size)
{
    GameGrid::Ptr c(new GameGrid(filename, size));
    c->self = c;
    return c;
}

GameGrid::~GameGrid() 
{
    for(size_t i = 0; i < GetGridSize(); ++i)
        delete [] Grid[i];
    delete [] Grid;
    
    for(size_t i = 0; i < GetGridSize(); ++i)
        delete [] GridThreads[i];
    delete [] GridThreads;
}

GameGrid::GameGrid(string filename, size_t size)
{
    this->filename = filename;
    Grid = new bool*[size];
    for(size_t i = 0; i < size; ++i)
        Grid[i] = new bool[size];

    GridThreads = new int*[size];
    for(size_t i = 0; i < size; ++i)
    {
        GridThreads[i] = new int[size];
        memset(GridThreads[i], 0, size*sizeof(int));
    }
    gridSize = size;
}

bool GameGrid::GetCellValue(size_t col, size_t row)
{
    return Grid[col][row];
}

int GameGrid::GetThreadValue(size_t col, size_t row)
{
    return GridThreads[col][row];
}
size_t GameGrid::GetGridSize()
{
    return gridSize;
}

void GameGrid::ParseInputFile()
{
    ifstream fin(filename.c_str());
    string line;
    

    for(int row = 0; !getline(fin, line).eof(); ++row)
    {
        vector<bool> values = tokenize(line);
        int col = 0;
        for(vector<bool>::iterator element = values.begin();
               element != values.end();
               ++element,  ++col)
        {
            Grid[col][row] = *element;
        }
    }
}

uint32_t GameGrid::CountLivingNeighbors(size_t col, size_t row)
{
    uint32_t livingNeighbors = 0;
    
    bool* cellPtr = 0;
    if(row != 0 && Grid[col][row-1] == true) //UP
        livingNeighbors++;
    if(row != GetGridSize()-1 && Grid[col][row+1] == true) //DOWN
        livingNeighbors++;
    if(col != GetGridSize()-1 && Grid[col+1][row] == true) // RIGHT
        livingNeighbors++;
    if(col != 0 && Grid[col-1][row] == true) //LEFT
        livingNeighbors++;
    if(row != 0 && col != GetGridSize()-1 && Grid[col+1][row-1] == true) //UP RIGHT
        livingNeighbors++;
    if(row != 0 && col != 0 && Grid[col-1][row-1] == true) //UP LEFT
        livingNeighbors++;
    if(row != GetGridSize()-1 && col != GetGridSize() - 1 && Grid[col+1][row+1] == true) //DOWN RIGHT
        livingNeighbors++;
    if(row != GetGridSize()-1 && col != 0 && Grid[col-1][row+1] == true) //DOWN LEFT
        livingNeighbors++;
    
    return livingNeighbors;
}

void GameGrid::CalculateGeneration()
{
    list<Update> delayedUpdates;
    
    for(size_t col = 0; col < GetGridSize(); ++col)
    {
        for(size_t row = 0; row < GetGridSize(); ++row)
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
                    delayedUpdates.push_back(u);
                }

                if(livingNeighbors >= 4)
                {
                    //Kill Cell
                    u.updateValue = false;
                    delayedUpdates.push_back(u);
                }
                /* else remain alive */
            }
            else
            {
                if(livingNeighbors == 3)
                {
                    //ConceiveCell
                    u.updateValue = true;
                    delayedUpdates.push_back(u);
                }
            }

        }
    }
    commitUpdates(delayedUpdates);
}

void GameGrid::commitUpdates(list<Update>const & updates)
{
    if(updates.size() == 0)
        return;
    // Commit all updates to the grid.
    for(list<Update>::const_iterator i = updates.begin();
            i != updates.end();
            ++i)
    {
        *(i->position) = i->updateValue;
        *(i->threadPosition) = i->threadId;
    }

}


vector<bool> GameGrid::tokenize(string line)
{
    // construct a stream from the string
	stringstream strstr(line);

	// use stream iterators to copy the stream to the vector as whitespace separated strings
	istream_iterator<bool> it(strstr);
	istream_iterator<bool> end;
	vector<bool> results(it, end);

	return results;
}

