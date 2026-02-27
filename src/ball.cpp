#include "ball.h"
#include <cmath>
static constexpr float GRAVITY = 80.0f;      // VERY weak gravity
static constexpr float RESTITUTION = 0.98f;  // Almost no energy loss
static constexpr float MIN_BOUNCE_SPEED = 40.0f;

Ball::Ball(float startX, float startY)
{
    position = { startX, startY };

    // Initial velocity (diagonal)
    velocity = { 400.0f, 300.0f };

    radius = 15.0f;
}
// Remove after testing

void Ball::Update(float dt, const Arena& arena)
{
    // Apply weak gravity
    velocity.y += GRAVITY * dt;

    // Move
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    // Left wall
    if (position.x - radius <= arena.GetLeft())
    {
        position.x = arena.GetLeft() + radius;
        velocity.x *= -1.0f;
    }

    // Right wall
    if (position.x + radius >= arena.GetRight())
    {
        position.x = arena.GetRight() - radius;
        velocity.x *= -1.0f;
    }

    // Ceiling
    if (position.y - radius <= arena.GetTop())
    {
        position.y = arena.GetTop() + radius;
        velocity.y *= -RESTITUTION;
    }

    // Floor
    if (position.y + radius >= arena.GetBottom())
    {
        position.y = arena.GetBottom() - radius;

        velocity.y *= -RESTITUTION;

        // Prevent tiny infinite bouncing
        if (fabs(velocity.y) < MIN_BOUNCE_SPEED)
        {
            velocity.y = -MIN_BOUNCE_SPEED;
        }
    }
}

void Ball::Draw() const
{
    DrawCircleV(position, radius, RED);
}