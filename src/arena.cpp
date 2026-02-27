#include "arena.h"

Arena::Arena(float width, float height)
{
    left = 0.0f;
    top = 0.0f;
    right = width;
    bottom = height;
}

void Arena::Draw() const
{
    int thickness = 4;

    // Top wall
    DrawRectangle((int)left, (int)top,
                  (int)(right - left), thickness, WHITE);

    // Bottom wall
    DrawRectangle((int)left, (int)(bottom - thickness),
                  (int)(right - left), thickness, WHITE);

    // Left wall
    DrawRectangle((int)left, (int)top,
                  thickness, (int)(bottom - top), WHITE);

    // Right wall
    DrawRectangle((int)(right - thickness), (int)top,
                  thickness, (int)(bottom - top), WHITE);
}

float Arena::GetLeft() const { return left; }
float Arena::GetRight() const { return right; }
float Arena::GetTop() const { return top; }
float Arena::GetBottom() const { return bottom; }