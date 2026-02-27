#include "raylib.h"
#include "arena.h"
#include "ball.h"

int main()
{
    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LLB");
    SetTargetFPS(60);

    Arena arena((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
    Ball ball(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime(); // frame-independent physics

        ball.Update(dt, arena);

        BeginDrawing();
        ClearBackground(BLACK);

        arena.Draw();
        ball.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}