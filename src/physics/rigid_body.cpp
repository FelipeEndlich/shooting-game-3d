#include "rigid_body.hpp"

using namespace physic;

RigidBody::RigidBody(int dimension)
{
    position_ = math::Vector::Zero(dimension);
    velocity_ = math::Vector::Zero(dimension);
    acceleration_ = math::Vector::Zero(dimension);
}

void RigidBody::Update(double dt)
{
    velocity_ += acceleration_ * dt;
    position_ += velocity_ * dt;
}