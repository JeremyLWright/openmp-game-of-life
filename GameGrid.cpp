#include "GameGrid.h"

GameGrid::Ptr GameGrid::construct()
{
    GameGrid::Ptr c(new GameGrid());
    c->self = c;
    return c;
}

GameGrid::~GameGrid() {}

GameGrid::GameGrid()
{
    boost::array<index, 2> shape = {{ 10, 10 }};
    Grid(shape);
}
