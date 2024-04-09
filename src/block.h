#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "color.h"

class Block
{
private:
    int cellSize;
    int rotationState;
    int colOffset;
    int rowOffset;
    std::vector<Color> colors;
public:
    Block();
    void draw(int offsetX, int offsetY);
    void move(int row, int col);
    std::vector<Position> getCellPositions();
    int id;
    std::map<int, std::vector<Position>> cells;
    void rotate();
    void undoRotate();
};