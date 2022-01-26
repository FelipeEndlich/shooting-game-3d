#include "rigidBody.hpp"

using namespace physic;

RigidBody::RigidBody(int dimension)
{
    position = math::Vector::Zero(dimension);
    velocity = math::Vector::Zero(dimension);
    acceleration = math::Vector::Zero(dimension);
}

void RigidBody::update(double dt)
{
    velocity += acceleration * dt;
    position += velocity * dt;
}