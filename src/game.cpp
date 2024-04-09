#include "game.h"
#include <random>

bool Game::isBlockOutside()
{
    std::vector<Position> tiles = currentBlock.getCellPositions();
    for (Position item : tiles)
    {
        if (grid.isCellOutside(item.row, item.col))
        {
            return true;
        }
    }
    return false;
}
void Game::rotateBlock()
{
    if (gameOver)
    {
        return;
    }
    currentBlock.rotate();
    if (isBlockOutside() || !blockFits())
    {
        currentBlock.undoRotate();
    }
}

void Game::reset()
{
    grid.initializeGrid();
    blocks = getAllBlocks();
    currentBlock = getRandomBlock();
    nextBlock = getRandomBlock();
    gameOver = false;
    score = 0;
}

void Game::updateScore(int linesCleared, int moveDownPoints)
{
    switch (linesCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    default:
        break;
    }

    score += moveDownPoints;
}


Game::Game()
{
    grid = Grid();
    blocks = getAllBlocks();
    currentBlock = getRandomBlock();
    nextBlock = getRandomBlock();
    gameOver = false;
    score = 0;
}

Block Game::getRandomBlock()
{
    if (blocks.size() == 0)
    {
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

std::vector<Block> Game::getAllBlocks()
{
    return {LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

bool Game::blockFits()
{
    std::vector<Position> tiles = currentBlock.getCellPositions();
    for (Position item : tiles)
    {
        if (!grid.isCellEmpty(item.row, item.col))
        {
            return false;
        }
    }
    return true;
}

void Game::draw()
{
    grid.drawGrid();
    currentBlock.draw(11, 11);
    switch (nextBlock.id)
    {
    case 3:
        nextBlock.draw(255, 290);
        break;
    
    case 4:
        nextBlock.draw(255, 280);
        break;
    default:
        nextBlock.draw(270, 270);
        break;
    
    }

}

void Game::handleInput()
{
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed == KEY_SPACE)
    {
        gameOver = false;
        reset();
    }
    switch (keyPressed)
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        moveBlockRight();
        break;
    case KEY_DOWN:
        moveBlockDown();
        updateScore(0, 1);
        break;
    case KEY_UP:
        rotateBlock();
        break;
    }
}

void Game::MoveBlockLeft()
{
    if (gameOver)
    {
        return;
    }

    currentBlock.move(0, -1);
    if (isBlockOutside() || !blockFits())
    {
        currentBlock.move(0, 1);
    }
}

void Game::moveBlockRight()
{
    if (gameOver)
    {
        return;
    }
    currentBlock.move(0, 1);
    if (isBlockOutside() || !blockFits())
    {
        currentBlock.move(0, -1);
    }
}

void Game::moveBlockDown()
{
    if (gameOver)
    {
        return;
    }
    currentBlock.move(1, 0);
    if (isBlockOutside() || !blockFits())
    {
        currentBlock.move(-1, 0);
        lockBlock();
    }
}

void Game::lockBlock()
{
    std::vector<Position> tiles = currentBlock.getCellPositions();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.col] = currentBlock.id;
    }
    currentBlock = nextBlock;
    nextBlock = getRandomBlock();
    int linesCleared = grid.clearFullRows();
    updateScore(linesCleared, 0);
    if (!blockFits())
    {
        // Game Over
        gameOver = true;
    }

    grid.clearFullRows();
}
