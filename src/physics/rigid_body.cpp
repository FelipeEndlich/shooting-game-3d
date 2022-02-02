#include "rigid_body.hpp"

#include "../math/vector.hpp"

using ::math::Vector;
using ::physic::RigidBody;

RigidBody::RigidBody(int dimension)
{
    position_ = math::Vector::Zero(dimension);
    set_last_position(position_);
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
    set_last_position(position_);
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

Vector RigidBody::get_last_position() const
{
    return last_position_;
}

void RigidBody::set_gravity_acceleration(Vector gravity_acceleration)
{
    gravity_acceleration_ = gravity_acceleration;
    weight_ = gravity_acceleration_ * mass_;
}

void RigidBody::set_last_position(Vector last_position)
{
    last_position_ = last_position;
}