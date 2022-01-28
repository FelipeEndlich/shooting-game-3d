#include "./character.hpp"

#include <iostream>
#include <cmath>

#include "./state/falling_state.hpp"
#include "../../../physics/rigid_body.hpp"
#include "../../shapes/circle.hpp"
#include "../../shapes/rectangle.hpp"
#include "../../color/rgba_factory.hpp"

using ::graphics::color::RGBA;
using ::graphics::elements::state::BaseState;
using ::graphics::elements::state::Character;
using ::graphics::elements::state::FallingState;
using ::graphics::shapes::Circle;
using ::graphics::shapes::Rectangle;
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

    outline_ = Rectangle(get_position(), get_width(), get_height(), color::RGBAFactory::get_color("black"));

    // Instantiate head
    double head_radius = radius * 0.3;
    Vector head_position = position_;
    head_position[1] += head_radius - radius;
    head_ = Circle(head_position, head_radius, color);

    // Instantiate body
    double body_width = radius * 0.3;
    double body_height = radius * 0.7;
    Vector body_position = position_;
    body_position[0] -= body_width / 2;
    body_position[1] = head_position[1] + head_radius;
    body_ = Rectangle(body_position, body_width, body_height, color);

    // Instantiate left thig
    double left_thig_width = radius * 0.15;
    double left_thig_height = radius * 0.5;
    Vector left_thig_position = body_position;
    left_thig_position[1] += body_height;
    left_thig_ = Rectangle(left_thig_position, left_thig_width, left_thig_height, color);

    Vector left_thig_center = left_thig_position;
    left_thig_center[0] += left_thig_width / 2;
    left_thig_.Rotate(left_thig_center, M_PI / 12);

    // Instantiate left thig
    double right_thig_width = radius * 0.15;
    double right_thig_height = radius * 0.5;
    Vector right_thig_position = body_position;
    right_thig_position[0] += body_width - right_thig_width;
    right_thig_position[1] += body_height;
    right_thig_ = Rectangle(right_thig_position, right_thig_width, right_thig_height, color);

    Vector right_thig_center = left_thig_position;
    right_thig_center[0] += left_thig_width / 2;
    right_thig_.Rotate(right_thig_center, -M_PI / 12);

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
        head_ = other.head_;
        body_ = other.body_;
        outline_ = other.outline_;
        left_thig_ = other.left_thig_;
        right_thig_ = other.right_thig_;
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
    outline_.Draw();
    //shape_.Draw();
    head_.Draw();
    body_.Draw();
    left_thig_.Draw();
    right_thig_.Draw();
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
    {
        state_->ProcessCollision(collidable);
    }
}

void Character::ProcessMove(double delta_time)
{
    Vector position = position_;
    Update(delta_time);
    Vector translate = position_ - position;
    outline_.Translate(translate);
    shape_.Translate(translate);
    head_.Translate(translate);
    body_.Translate(translate);
    left_thig_.Translate(translate);
    right_thig_.Translate(translate);
}

void Character::ProcessCollisionByLeft(ICollidable *collidable)
{
    double collidable_x = collidable->get_position()[0] + collidable->get_width();
    double character_x = get_position()[0];
    Translate(collidable_x - character_x, 0);
}

void Character::ProcessCollisionByRight(ICollidable *collidable)
{
    double collidable_x = collidable->get_position()[0];
    double character_x = get_position()[0] + get_width();
    Translate(collidable_x - character_x, 0);
}

void Character::ProcessCollisionByTop(ICollidable *collidable)
{
    double collidable_y = collidable->get_position()[1] + collidable->get_height();
    double character_y = get_position()[1];
    Translate(0, collidable_y - character_y);
}

void Character::ProcessCollisionByBottom(ICollidable *collidable)
{
    double collidable_y = collidable->get_position()[1];
    double character_y = get_position()[1] + get_height();
    Translate(0, collidable_y - character_y);
}

void Character::ProcessGravity()
{
    state_->ProcessGravity();
}

void Character::Translate(double dx, double dy)
{
    Vector translation(2);
    translation[0] = dx;
    translation[1] = dy;
    Translate(translation);
}

void Character::Translate(math::Vector &translation)
{
    shape_.Translate(translation);
    head_.Translate(translation);
    body_.Translate(translation);
    outline_.Translate(translation);
    left_thig_.Translate(translation);
    right_thig_.Translate(translation);
    position_ += translation;
}