#pragma once
#include "grid.h"
#include "block.h"
#include "blocks.cpp"

class Game
{
private:
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    bool isBlockOutside();
    void rotateBlock();
    void reset();
    void updateScore(int linesCleared, int moveDownPoints);
    Block getRandomBlock();
    std::vector<Block> getAllBlocks();
    void MoveBlockLeft();
    void moveBlockRight();
    Grid grid;
public:
    void moveBlockDown();
    int score;
    Game();
    bool blockFits();
    void draw();
    void handleInput();

    void lockBlock();
    bool gameOver;
};