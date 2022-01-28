#include "./character.hpp"

#include <iostream>

#include "./state/falling_state.hpp"
#include "../../../physics/rigid_body.hpp"

using ::graphics::color::RGBA;
using ::graphics::elements::state::BaseState;
using ::graphics::elements::state::Character;
using ::graphics::elements::state::FallingState;
using ::graphics::shapes::Circle;
using ::math::Vector;
using ::physic::Direction;
using ::physic::ICollidable;
using ::std::cout;
using ::std::endl;

Character::Character(bool collision_processable)
    : RigidBody(2)
{
    collision_processable_ = collision_processable;
    Allocate();
}

Character::Character(Vector &initial_position, double radius, RGBA &color, bool collision_processable)
    : RigidBody(2)
{
    collision_processable_ = collision_processable;
    position_ = initial_position;
    shape_ = Circle(position_, radius, color);

    double time_jump_max = 1000;
    Vector gravity_acceleration = Vector::Zero(2);
    gravity_acceleration[1] = 12 * radius / (time_jump_max * time_jump_max);
    set_gravity_acceleration(gravity_acceleration);

    initial_jump_velocity_ = gravity_acceleration * time_jump_max * -1;

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
        position_ = other.position_;
        shape_ = other.shape_;
        velocity_ = other.velocity_;
        acceleration_ = other.acceleration_;
        last_position_ = other.last_position_;

        Deallocate();
        this->state_ = other.state_->Clone();
    }
    return *this;
}

void Character::Render()
{
    shape_.Draw();
}

void Character::Jump(double delta_time)
{
    state_->Jump(delta_time);
}

void Character::Jump(double delta_time, physic::Direction direction)
{
    state_->Jump(delta_time, direction);
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
    //cout << "Character::setState() " << state->to_string() << endl;
}

void Character::Allocate()
{
    state_ = new FallingState(this);
}

void Character::Deallocate()
{
    delete state_;
}

Vector Character::get_position()
{
    Vector position(position_);
    position[0] -= shape_.get_radius();
    position[1] -= shape_.get_radius();

    return position;
}

double Character::get_width()
{
    return shape_.get_radius() * 2;
}

double Character::get_height()
{
    return shape_.get_radius() * 2;
}
void Character::ProcessCollision(ICollidable *collidable)
{
    if (collision_processable_)
        state_->ProcessCollision(collidable);
}

void Character::ProcessMove(double delta_time)
{
    Vector position = position_;
    Update(delta_time);
    Vector translate = position_ - position;
    shape_.Translate(translate);
}

void Character::ProcessCollisionByLeft(ICollidable *collidable)
{
    double collidable_x = collidable->get_position()[0] + collidable->get_width();
    double character_x = get_position()[0];

    Vector translate = Vector::Zero(2);
    translate[0] = collidable_x - character_x;

    shape_.Translate(translate);
    position_ += translate;
}

void Character::ProcessCollisionByRight(ICollidable *collidable)
{
    double collidable_x = collidable->get_position()[0];
    double character_x = get_position()[0] + get_width();

    Vector translate = Vector::Zero(2);
    translate[0] = collidable_x - character_x;

    shape_.Translate(translate);
    position_ += translate;
}

void Character::ProcessCollisionByTop(ICollidable *collidable)
{
    double collidable_y = collidable->get_position()[1] + collidable->get_height();
    double character_y = get_position()[1];

    Vector translate = Vector::Zero(2);
    translate[1] = collidable_y - character_y;

    shape_.Translate(translate);
    position_ += translate;
}

void Character::ProcessCollisionByBottom(ICollidable *collidable)
{
    double collidable_y = collidable->get_position()[1];
    double character_y = get_position()[1] + get_height();

    Vector translate = Vector::Zero(2);
    translate[1] = collidable_y - character_y;

    shape_.Translate(translate);
    position_ += translate;
}

void Character::ProcessGravity()
{
    state_->ProcessGravity();
}