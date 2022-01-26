#include "rigidBody.hpp"

using namespace physic;

RigidBody::RigidBody(int dimension)
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