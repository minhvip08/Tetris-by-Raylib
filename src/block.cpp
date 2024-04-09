#include "block.h"
#include <iostream>

Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = getCellColors();
    colOffset = 0;
    rowOffset = 0;
}

void Block::draw(int offsetX, int offsetY) 
{
    std::vector<Position> titles =getCellPositions();
    for (Position item: titles){
        DrawRectangle(item.col * cellSize +offsetX, item.row * cellSize +offsetY, cellSize -1 , cellSize -1, colors[id]);
    }
    
}

void Block::move(int row, int col)
{
    colOffset += col;
    rowOffset += row;
}

std::vector<Position> Block::getCellPositions()
{
    std::vector<Position> titles = cells[rotationState];
    std::vector<Position> movedTitles;
    for (Position item: titles){
        movedTitles.push_back(Position(item.row + rowOffset, item.col + colOffset));
    }
    return movedTitles;
}

void Block::rotate()
{
    if (id == 4){
        return;
    }
    rotationState = (rotationState + 1) % 4;

    
}

void Block::undoRotate()
{
    if (id == 4){
        return;
    }
    rotationState = rotationState - 1;
    if (rotationState < 0){
        rotationState = cells.size() - 1;
    }
}
