#include "rigid_body.hpp"

#include "../math/vector.hpp"

using ::math::Vector;
using ::physic::RigidBody;

RigidBody::RigidBody(int dimension)
{
    position_ = math::Vector::Zero(dimension);
    velocity_ = math::Vector::Zero(dimension);
    acceleration_ = math::Vector::Zero(dimension);
    external_force_ = math::Vector::Zero(dimension);
    mass_ = 1;

    weight_ = math::Vector::Zero(dimension);
    weight_[1] = kGravityAcceleration * mass_;
}

void RigidBody::Update(double dt)
{
    Vector forces = weight_ + external_force_;
    acceleration_ = forces / mass_;
    velocity_ += acceleration_ * dt;
    position_ += velocity_ * dt;
}

double RigidBody::get_mass() const
{
    return mass_;
}