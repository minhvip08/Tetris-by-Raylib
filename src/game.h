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
public:
    Game();
    Block getRandomBlock();
    std::vector<Block> getAllBlocks();

    void draw();
    void handleInput();

    void MoveBlockLeft();

    void moveBlockRight();

    void moveBlockDown();
    void lockBlock();

    Grid grid;
};