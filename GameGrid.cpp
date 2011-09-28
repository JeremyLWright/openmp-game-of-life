#include "GameGrid.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <list>
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
    
    struct Update {
        bool updateValue;
        bool* position;
    };
}

GameGrid::Ptr GameGrid::construct(string filename, size_t size)
{
    GameGrid::Ptr c(new GameGrid(filename, size));
    c->self = c;
    return c;
}

GameGrid::~GameGrid() {}

GameGrid::GameGrid(string filename, size_t size)
{
    this->filename = filename;
    Grid = new bool*[size];
    for(size_t i = 0; i < size; ++i)
        Grid[i] = new bool[size];
    gridSize = size;
}

bool GameGrid::GetCellValue(size_t col, size_t row)
{
    return Grid[col][row];
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

bool GameGrid::MovePtr(bool** cellPtr, Direction direction, size_t col, size_t row)
{
    switch(direction)
    {
        case UP:
            if(row == 0)
                *cellPtr = 0; //Contribute nothing.
            else
                *cellPtr = &(Grid[col][row-1]);
            break;
        case UP_RIGHT:
            if(row == 0 || col == GetGridSize()-1)
                *cellPtr = 0;
            else
                *cellPtr = &(Grid[col+1][row-1]);
        case UP_LEFT:
            if(row == 0 || col == 0)
                *cellPtr = 0;
            else
                *cellPtr = &(Grid[col-1][row-1]);
        case DOWN:
            if(row == GetGridSize()-1)
                *cellPtr = 0;
            else
                *cellPtr = &(Grid[col][row+1]);
            break;
        case DOWN_RIGHT:
            if(row == GetGridSize()-1 || col == GetGridSize()-1)
                *cellPtr = 0;
            else
                *cellPtr = &(Grid[col+1][row+1]);
        case DOWN_LEFT:
            if(row == GetGridSize()-1 || col == 0)
                *cellPtr = 0;
            else
                *cellPtr = &(Grid[col-1][row+1]);
        case RIGHT:
            if(col == GetGridSize()-1)
                *cellPtr = 0;
            else
                *cellPtr = &(Grid[col+1][row]);
            break;
        case LEFT:
            if(col == 0)
                *cellPtr = 0;
            else
                *cellPtr = &(Grid[col-1][row]);
            break;
    }

    return (*cellPtr != 0) ? true : false;


}

uint32_t GameGrid::CountLivingNeighbors(size_t col, size_t row)
{
    uint32_t livingNeighbors = 0;
    
    bool* cellPtr = 0;
    if(MovePtr(&cellPtr, UP, col, row))
        *cellPtr ? livingNeighbors++ : 0;
    if(MovePtr(&cellPtr, DOWN, col, row))
        *cellPtr ? livingNeighbors++ : 0;
    if(MovePtr(&cellPtr, LEFT, col, row))
        *cellPtr ? livingNeighbors++ : 0;
    if(MovePtr(&cellPtr, RIGHT, col, row))
        *cellPtr ? livingNeighbors++ : 0;
    if(MovePtr(&cellPtr, UP_LEFT, col, row))
        *cellPtr ? livingNeighbors++ : 0;
    if(MovePtr(&cellPtr, UP_RIGHT, col, row))
        *cellPtr ? livingNeighbors++ : 0;
    if(MovePtr(&cellPtr, DOWN_LEFT, col, row))
        *cellPtr ? livingNeighbors++ : 0;
    if(MovePtr(&cellPtr, DOWN_RIGHT, col, row))
        *cellPtr ? livingNeighbors++ : 0;
    
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
            cout << "Row: " << row 
                << "Col: " << col
                << ": " << livingNeighbors << endl;
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
    }

    // Commit all updates to the grid.
    for(list<Update>::const_iterator i = delayedUpdates.begin();
            i != delayedUpdates.end();
            ++i)
    {
        *(i->position) = i->updateValue;
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

