#pragma once
#include "raylib.h"
#include "arena.h"

class Ball
{
private:
    Vector2 position;
    Vector2 velocity;
    float radius;

public:
    Ball(float startX, float startY);

    void Update(float dt, const Arena& arena);
    void Draw() const;
};