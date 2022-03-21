#include "obstacle.hpp"

using ::graphics::color::RGBA;
using ::graphics::elements::Obstacle;
using ::graphics::shapes::Cuboid;
using ::math::Vector;
using ::physic::ICollidable;

#include <iostream>
using namespace std;

Obstacle::Obstacle(double x, double y, double z, double width, double height, double depth, RGBA &color)
    : RigidBody(3)
{
    Vector initial_position = Vector::ThreeDimPoint(x, y, z);
    position_ = initial_position;
    shape_ = new Cuboid(position_, width, height, depth, color);
}
        

Obstacle::Obstacle(Vector &initial_position, double width, double height, double depth, RGBA &color)
    : RigidBody(3)
{
    position_ = initial_position;
    shape_ = new Cuboid(position_, width, height, depth, color);
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