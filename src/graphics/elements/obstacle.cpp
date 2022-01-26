#include "obstacle.hpp"

using graphics::color::RGBA;
using graphics::elements::Obstacle;
using graphics::shapes::Rectangle;
using math::Vector;

Obstacle::Obstacle(Vector &initial_position, double width, double height, RGBA &color)
    : RigidBody(2)
{
    position_ = initial_position;
    shape_ = Rectangle(position_, width, height, color);
}

void Obstacle::Render()
{
    shape_.Draw();
}