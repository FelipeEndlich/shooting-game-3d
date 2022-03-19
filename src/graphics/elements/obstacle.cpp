#include "obstacle.hpp"

using ::graphics::color::RGBA;
using ::graphics::elements::Obstacle;
using ::graphics::shapes::Cuboid;
using ::math::Vector;
using ::physic::ICollidable;

#include <iostream>
using namespace std;

Obstacle::Obstacle(Vector &initial_position, double width, double height, RGBA &color)
    : RigidBody(2)
{
    position_ = initial_position;
    shape_ = new Cuboid(position_, width, height, color);
}

Obstacle::~Obstacle()
{
    delete shape_;
}

void Obstacle::Render()
{
    shape_->Draw();
}

Vector Obstacle::get_position()
{
    return position_;
}

double Obstacle::get_width()
{
    return shape_->get_width();
}

double Obstacle::get_height()
{
    return shape_->get_height();
}

void Obstacle::ProcessCollision(ICollidable *collidable)
{
}