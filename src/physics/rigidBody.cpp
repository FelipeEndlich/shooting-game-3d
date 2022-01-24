#include "rigidBody.hpp"

using namespace physics;

RigidBody::RigidBody(int dimension, double width, double height)
{
    position = math::Vector::zero(dimension);
    velocity = math::Vector::zero(dimension);
    acceleration = math::Vector::zero(dimension);
}

void RigidBody::update(double dt)
{
    velocity += acceleration * dt;
    position += velocity * dt;
}