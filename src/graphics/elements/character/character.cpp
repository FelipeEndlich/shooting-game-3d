#include "./character.hpp"

#include <iostream>

#include "./state/grounded_state.hpp"
#include "../../../physics/rigidBody.hpp"

using ::graphics::color::RGBA;
using ::graphics::elements::state::BaseState;
using ::graphics::elements::state::Character;
using ::graphics::elements::state::GroundedState;
using ::graphics::shapes::Circle;
using ::math::Vector;
using ::std::cout;
using ::std::endl;

Character::Character()
    : RigidBody(2)
{
    Allocate();
}

Character::Character(Vector &initial_position, double radius, RGBA &color)
    : RigidBody(2)
{
    position = initial_position;
    shape_ = Circle(position, radius, color);
    Allocate();
}

Character::~Character()
{
    Deallocate();
}

Character &Character::operator=(const Character &other)
{
    if (this != &other)
    {
        position = other.position;
        shape_ = other.shape_;
        velocity = other.velocity;
        acceleration = other.acceleration;

        Deallocate();
        this->state_ = other.state_->Clone();
    }
    return *this;
}

void Character::Render()
{
    shape_.draw();
}

void Character::Fall(double delta_time)
{
    state_->Fall(delta_time);
}

void Character::Jump(double delta_time)
{
    state_->Jump(delta_time);
}

void Character::Stop(double delta_time)
{
    state_->Stop(delta_time);
}

void Character::Move(double delta_time, Direction direction)
{
    state_->Move(delta_time, direction);
}

void Character::set_state(BaseState *state)
{
    Deallocate();
    this->state_ = state;
    cout << "Character::setState() " << state->to_string() << endl;
}

void Character::Allocate()
{
    state_ = new GroundedState(this);
}

void Character::Deallocate()
{
    delete state_;
}
