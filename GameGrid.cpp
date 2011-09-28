#include "GameGrid.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <iostream>
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

GameGrid::~GameGrid() {}

GameGrid::GameGrid(string filename, size_t size)
{
    this->filename = filename;
    Grid = new bool*[size];
    for(int i = 0; i < size; ++i)
        Grid[i] = new bool[size];
}

void GameGrid::ParseInputFile()
{
    ifstream fin(filename.c_str());
    string line;
    

    for(int row = 0; !getline(fin, line).eof(); ++row)
    {
        vector<string> values = tokenize(line);
        int col = 0;

        for(vector<string>::iterator element = values.begin();
               element != values.end();
               ++element,  ++col)
        {
            bool b;
            from_string<bool>(b, *element, std::dec);
            Grid[col][row] = b;
        }
    }
}

vector<string> GameGrid::tokenize(string line)
{
    // construct a stream from the string
	stringstream strstr(line);

	// use stream iterators to copy the stream to the vector as whitespace separated strings
	istream_iterator<string> it(strstr);
	istream_iterator<string> end;
	vector<string> results(it, end);

	return results;
}

