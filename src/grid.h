#pragma once
#include <vector>   
#include <raylib.h>

class Grid {
    private:
        int numRows;
        int numCols;
        int cellSize;
        std::vector<Color> colors;
        bool isRowFull(int row);
        void clearRow(int row);
        void moveRowsDown(int row, int numRowsToMoveDown);
    public:
        Grid();
        bool isCellEmpty(int row, int col);
        void initializeGrid();
        int grid[20][20];
        void printGrid();
        void drawGrid();
        bool isCellOutside(int row, int col);
        // std::vector<Color> getCellColors();
        int clearFullRows();

    
};
