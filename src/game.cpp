#include "game.h"
#include  <random>

bool Game::isBlockOutside()
{
    std::vector<Position> tiles = currentBlock.getCellPositions();
    for (Position item: tiles){
        if (grid.isCellOutside(item.row, item.col)){
            return true;
        }   
    }
    return false;
}
void Game::rotateBlock()
{
    currentBlock.rotate();
    if (isBlockOutside())
    {
        currentBlock.undoRotate();
    }
}
Game::Game()
{
    grid = Grid();
    blocks = getAllBlocks();
    currentBlock = getRandomBlock();
    nextBlock = getRandomBlock();
}

Block Game::getRandomBlock() {
    if (blocks.size() == 0) {
        blocks = getAllBlocks();
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, blocks.size() - 1);
    int random = dis(gen);
    Block block = blocks[random];
    blocks.erase(blocks.begin() + random);
    return block;
}

std::vector<Block> Game::getAllBlocks() {
    return {LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::draw() {
    grid.drawGrid();
    currentBlock.draw();
//    nextBlock.draw();
}

void Game::handleInput()
{
    int keyPressed = GetKeyPressed();
    switch(keyPressed){
        case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
            moveBlockRight();
            break;
        case KEY_DOWN:
            moveBlockDown();
            break;
        case KEY_UP:
            rotateBlock();
            break;
    }
}

void Game::MoveBlockLeft()
{
    currentBlock.move(0, -1);
    if (isBlockOutside())
    {
        currentBlock.move(0, 1);
    }
    
}

void Game::moveBlockRight()
{
    currentBlock.move(0, 1);
    if (isBlockOutside())
    {
        currentBlock.move(0, -1);
    }
}

void Game::moveBlockDown()
{
    currentBlock.move(1, 0);
    if (isBlockOutside())
    {
        currentBlock.move(-1, 0);
        lockBlock();

    }
 }

 void Game::lockBlock()
 {
        std::vector<Position> tiles = currentBlock.getCellPositions();
        for (Position item: tiles){
            grid.grid[item.row][item.col] = currentBlock.id;
        }
        currentBlock = nextBlock;
        nextBlock = getRandomBlock();
 }
