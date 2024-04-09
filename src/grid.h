#pragma once
#include <vector>   
#include <raylib.h>

class Grid {
    private:
        int numRows;
        int numCols;
        int cellSize;
        std::vector<Color> colors;
    public:
        Grid();
        bool isCellEmpty(int row, int col);
        void initializeGrid();
        int grid[20][20];
        void printGrid();
        void drawGrid();
        bool isCellOutside(int row, int col);
        // std::vector<Color> getCellColors();

    
};
