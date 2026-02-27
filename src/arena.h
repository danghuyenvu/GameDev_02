#pragma once
#include "raylib.h"

class Arena
{
private:
    float left;
    float right;
    float top;
    float bottom;

public:
    Arena(float width, float height);

    void Draw() const;

    float GetLeft() const;
    float GetRight() const;
    float GetTop() const;
    float GetBottom() const;
};