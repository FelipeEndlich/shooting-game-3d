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

    gravity_acceleration_ = math::Vector::Zero(dimension);
    gravity_acceleration_[1] = 0.001;

    weight_ = gravity_acceleration_ * mass_;
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

Vector RigidBody::get_gravity_acceleration() const
{
    return gravity_acceleration_;
}

Vector RigidBody::get_weight() const
{
    return weight_;
}

void RigidBody::set_gravity_acceleration(math::Vector gravity_acceleration)
{
    gravity_acceleration_ = gravity_acceleration;
    weight_ = gravity_acceleration_ * mass_;
}