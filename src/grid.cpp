
#include "grid.h"
#include "color.h"
#include <iostream>

bool Grid::isRowFull(int row)
{
    for(int i = 0; i < numCols; i++)
    {
        if (grid[row][i] == 0)
        {
            return false;
        }
    }
    return true;
}

void Grid::clearRow(int row)
{
    for (int col = 0; col < numCols; col++)
    {
        grid[row][col] = 0;
    }
}

void Grid::moveRowsDown(int row, int numRowsToMoveDown)
{
     for (int col = 0; col < numCols; col++){
        grid[row + numRowsToMoveDown][col] = grid[row][col];
        grid[row][col] = 0;
     }
}

int Grid::clearFullRows()
{
    int completedRows = 0;
    for (int row = numRows-1 ; row >= 0; row--)
    {
        if (isRowFull(row))
        {
            clearRow(row);

            completedRows++;
        }
        else if (completedRows > 0)
        {
            moveRowsDown(row, completedRows);
        }
    }

    return completedRows;
}

Grid::Grid()
{
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    initializeGrid();
    colors = getCellColors();
}

bool Grid::isCellEmpty(int row, int col)
{
    if (grid[row][col] == 0)
    {
        return true;
    }
    return false;
}

void Grid::initializeGrid()
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            grid[i][j] = 0;
        }
    }
}

void Grid::printGrid()
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// std::vector<Color> Grid::getCellColors()
// {
//     Color darkGrey = {26, 31, 40, 255};
//     Color green = {47, 230, 23, 255};
//     Color red = {232, 18, 18, 255};
//     Color orange = {226, 116, 17, 255};
//     Color yellow = {237, 234, 4, 255};
//     Color purple = {166, 0, 247, 255};
//     Color cyan = {21, 204, 209, 255};
//     Color blue = {13, 64, 216, 255};

//     return {darkGrey, green, red, orange, yellow, purple, cyan, blue};
// }

void Grid::drawGrid()
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            int cellValue = grid[i][j];
            Color cellColor = colors[cellValue];
            DrawRectangle(j * cellSize + 11, i * cellSize + 11, cellSize -1 , cellSize -1, cellColor);
        }
    }
}

bool Grid::isCellOutside(int row, int col)
{
    if (row >= 0 && row < numRows && col >= 0 && col < numCols)
    {
        return false;
    }
    return true;
}
