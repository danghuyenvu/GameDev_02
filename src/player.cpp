#pragma once
#include "raylib.h"
#include "Arena.h"

class Player
{
public:
    Rectangle body;
    Vector2 velocity;

    Player(float x, float y);

    void Update(float dt, const Arena& arena);
    void Draw();
};