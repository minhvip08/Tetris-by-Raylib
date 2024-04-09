#include <raylib.h>
#include "game.h"
#include "color.h"
#include <iostream>

double lastUpdateTime = 0;

bool EventTriggered(double time)
{
    if (GetTime() - lastUpdateTime > time)
    {
        lastUpdateTime = GetTime();
        return true;
    }
    return false;
}
 
int main()
{
    Color color = {44,44,127,255};
    InitWindow(500, 620, "Hello World");
    SetTargetFPS(60);

    Font font = LoadFontEx("resources/monogram.ttf", 64, 0, 0);

    Game game = Game();

    while (WindowShouldClose() == false)
    {
        game.handleInput();
        if (EventTriggered(0.2))
            game.moveBlockDown();

        BeginDrawing();
        ClearBackground(color);
        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        if (game.gameOver)
            DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, WHITE);
        DrawRectangleRounded({320, 50, 170, 60}, 0.3, 6, lightBlue);
        
        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);


        DrawTextEx(font, scoreText, {320 + (170 -textSize.x)/2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);

        game.draw();
        EndDrawing();
    }
    CloseWindow();
}