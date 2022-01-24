#include "obstacle.hpp"

using namespace graphics::elements;

Obstacle::Obstacle(Vector &initialPosition, double width, double height, RGBA &color)
    : RigidBody(2)
{
    position = initialPosition;
    shape = Rectangle(position, width, height, color);
}

void Obstacle::render()
{
    shape.draw();
}