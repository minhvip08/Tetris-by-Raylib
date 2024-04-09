#include <raylib.h>
#include "game.h"

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
    InitWindow(300, 600, "Hello World");
    SetTargetFPS(60);

    Game game = Game();

    while (WindowShouldClose() == false)
    {
        game.handleInput();
        if (EventTriggered(0.7))
            game.moveBlockDown();

        BeginDrawing();
        ClearBackground(color);
        game.draw();
        EndDrawing();
    }
    CloseWindow();
}