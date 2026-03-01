#include <SDL3/SDL.h>
#include <iostream>

#include "game.h"
#include "arena.h"
#include "ball.h"
#include "player.h"
#include "menu.h"

int main(int argc, char* argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
        return -1;
    }

    GameWindow *window = new GameWindow();
    if (window->init("Ricochet test") != 0){
        std::cerr << "Failed to initialize GameWindow: " << SDL_GetError() << std::endl;
        delete(window);
        SDL_Quit();
        return -1;
    }

    // --- Initialize Menu ---
    Menu menu;
    GameState gameState = GameState::MENU;
    
    // Game objects (sẽ được khởi tạo khi chọn map)
    Arena* arena = nullptr;
    Ball* ball = nullptr;
    Player* player = nullptr;
    Player* player2 = nullptr;
    Vector2 ballStartPos;

    bool running = true;

    Uint64 lastCounter = SDL_GetPerformanceCounter();
    Uint64 frequency = SDL_GetPerformanceFrequency();

    while (running)
    {
        // ---- Events ----
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;

            if (event.type == SDL_EVENT_KEY_DOWN &&
                event.key.repeat == false)
            {
                if (gameState == GameState::GAMEPLAY)
                {
                    if (event.key.scancode == SDL_SCANCODE_J)
                    {
                        player->PerformAttack(*ball);
                    }
                    else if (event.key.scancode == SDL_SCANCODE_RSHIFT)
                    {
                        player2->PerformAttack(*ball);
                    }
                    // ESC để quay lại menu
                    else if (event.key.scancode == SDL_SCANCODE_ESCAPE)
                    {
                        gameState = GameState::MENU;
                        menu.Reset();
                        delete arena;
                        delete ball;
                        delete player;
                        delete player2;
                        arena = nullptr;
                        ball = nullptr;
                        player = nullptr;
                        player2 = nullptr;
                    }
                }
            }
        }

        // ---- Delta Time (High Precision) ----
        Uint64 currentCounter = SDL_GetPerformanceCounter();
        float deltaTime = (float)(currentCounter - lastCounter) / frequency;
        lastCounter = currentCounter;

        // Optional safety clamp (prevents physics explosion if debugging)
        if (deltaTime > 0.016f)
            deltaTime = 0.016f;

        // ---- Input & Update ----
        const bool* keyboardState = SDL_GetKeyboardState(nullptr);
        
        if (gameState == GameState::MENU)
        {
            menu.HandleInput(keyboardState);
            
            if (menu.IsMapSelected())
            {
                // Khởi tạo game với map được chọn
                const MapConfig& selectedMap = menu.GetSelectedMap();
                
                ballStartPos = selectedMap.ballSpawnPos;
                arena = new Arena(selectedMap.width, selectedMap.height, selectedMap.wallThickness);
                ball = new Ball(ballStartPos, 20.0f);
                player = new Player(selectedMap.player1SpawnPos);
                player2 = new Player(selectedMap.player2SpawnPos, 2);
                
                gameState = GameState::GAMEPLAY;
            }
        }
        else if (gameState == GameState::GAMEPLAY)
        {
            bool hurted = player->Check_collision(*ball) || player2->Check_collision(*ball);
            if (hurted){
                ball->GetRect().x = ballStartPos.x;
                ball->GetRect().y = ballStartPos.y;
                ball->setVelocity(Vector2(0.0f, 0.0f));
            }
            
            player->HandleInput(keyboardState);
            player2->HandleInput(keyboardState);
            
            // ---- Update ----
            ball->Update(deltaTime);
            arena->CheckCollision(ball->GetRect(), ball->getVelocity());

            player->Update(deltaTime, arena->GetWidth(), arena->GetHeight(), 10);
            player2->Update(deltaTime, arena->GetWidth(), arena->GetHeight(), 10);
        }
        
        // ---- Render ----
        SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);
        SDL_RenderClear(window->renderer);

        if (gameState == GameState::MENU)
        {
            menu.Render(window->renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
        }
        else if (gameState == GameState::GAMEPLAY)
        {
            arena->Render(window->renderer);
            ball->Render(window->renderer);
            player->Render(window->renderer);
            player2->Render(window->renderer);
        }
        
        SDL_RenderPresent(window->renderer);
    }
    
    // Cleanup
    if (arena) delete arena;
    if (ball) delete ball;
    if (player) delete player;
    if (player2) delete player2;
    delete(window);
    SDL_Quit();

    return 0;
}