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

    double time_jump_max = 1000;
    Vector gravity_acceleration = Vector::Zero(2);
    gravity_acceleration[1] = 12 * radius / (time_jump_max * time_jump_max);
    set_gravity_acceleration(gravity_acceleration);

    initial_jump_velocity_ = gravity_acceleration * time_jump_max * -1;

    InstantiateCharacter(radius, color);
    Allocate();
}

Character::~Character()
{
    Deallocate();
}

void Character::InstantiateCharacter(double radius, graphics::color::RGBA &color)
{
    // Radius factors
    double head_radius_factor = 0.3;

    // Height factors
    double body_height_factor = 0.7;
    double leg_height_factor = 0.35;
    double arm_height_factor = 0.7;

    // Width factors
    double body_width_factor = 0.15;
    double leg_width_factor = 0.15;
    double arm_width_factor = 0.15;

    // Rotate factors
    double arm_rotate_factor = M_PI / 6;
    double leg_rotate_factor = M_PI / 12;

    // Instantiate head
    double head_radius = radius * head_radius_factor;
    Vector head_position = position_;
    head_position[1] += head_radius - radius;
    head_ = Circle(head_position, head_radius, color);

    // Instantiate body
    double body_width = radius * body_width_factor;
    double body_height = radius * body_height_factor;
    Vector body_position = position_;
    body_position[0] -= body_width / 2;
    body_position[1] = head_position[1] + head_radius;
    body_ = Rectangle(body_position, body_width, body_height, color);

    // Instantiate left arm
    double left_arm_width = radius * arm_width_factor;
    double left_arm_height = radius * arm_height_factor;
    Vector left_arm_position = body_position;
    left_arm_position[0] += (body_width - left_arm_width) / 2;
    left_arm_ = Rectangle(left_arm_position, left_arm_width, left_arm_height, color);

    Vector left_arm_center = left_arm_position;
    left_arm_center[0] += left_arm_width / 2;
    left_arm_.Rotate(left_arm_center, arm_rotate_factor);

    // Instantiate left leg
    double left_thig_width = radius * leg_width_factor;
    double left_thig_height = radius * leg_height_factor;
    Vector left_thig_position = body_position;
    left_thig_position[0] += (body_width - left_thig_width) / 2;
    left_thig_position[1] += body_height;
    left_thig_ = Rectangle(left_thig_position, left_thig_width, left_thig_height, color);

    double left_calf_width = radius * leg_width_factor;
    double left_calf_height = radius * leg_height_factor;
    Vector left_calf_position = left_thig_position;
    left_calf_position[1] += left_thig_height;
    left_calf_ = Rectangle(left_calf_position, left_calf_width, left_calf_height, color);

    Vector left_thig_center = left_thig_position;
    left_thig_center[0] += left_thig_width / 2;
    left_thig_.Rotate(left_thig_center, leg_rotate_factor);
    left_calf_.Rotate(left_thig_center, leg_rotate_factor);

    // Instantiate right arm
    double right_arm_width = radius * arm_width_factor;
    double right_arm_height = radius * arm_height_factor;
    Vector right_arm_position = body_position;
    right_arm_position[0] += (body_width - right_arm_width) / 2;
    right_arm_ = Rectangle(right_arm_position, right_arm_width, right_arm_height, color);

    Vector right_arm_center = right_arm_position;
    right_arm_center[0] += right_arm_width / 2;
    right_arm_.Rotate(right_arm_center, -arm_rotate_factor);

    // Instantiate right leg
    double right_thig_width = radius * leg_width_factor;
    double right_thig_height = radius * leg_height_factor;
    Vector right_thig_position = body_position;
    right_thig_position[0] += (body_width - right_thig_width) / 2;
    right_thig_position[1] += body_height;
    right_thig_ = Rectangle(right_thig_position, right_thig_width, right_thig_height, color);

    double right_calf_width = radius * leg_width_factor;
    double right_calf_height = radius * leg_height_factor;
    Vector right_calf_position = right_thig_position;
    right_calf_position[1] += right_thig_height;
    right_calf_ = Rectangle(right_calf_position, right_calf_width, right_calf_height, color);

    Vector right_thig_center = left_thig_position;
    right_thig_center[0] += left_thig_width / 2;
    right_thig_.Rotate(right_thig_center, -leg_rotate_factor);
    right_calf_.Rotate(right_thig_center, -leg_rotate_factor);

    // Set characters width and height
    width_ = body_width;
    height_ = radius * 2;

    outline_ = Rectangle(get_position(), get_width(), get_height(), color::RGBAFactory::get_color("black"));
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
        left_arm_ = other.left_arm_;
        left_thig_ = other.left_thig_;
        left_calf_ = other.left_calf_;
        right_arm_ = other.right_arm_;
        right_thig_ = other.right_thig_;
        right_calf_ = other.right_calf_;
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
    //outline_.Draw();
    head_.Draw();
    body_.Draw();
    left_arm_.Draw();
    left_thig_.Draw();
    left_calf_.Draw();
    right_arm_.Draw();
    right_thig_.Draw();
    right_calf_.Draw();
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
    graphics::shapes::Rectangle left_arm_;
    state_ = new FallingState(this);
}

void Character::Deallocate()
{
    delete state_;
}

Vector Character::get_position()
{
    Vector position(position_);
    position[0] -= width_ / 2;
    position[1] -= height_ / 2;

    return position;
}

double Character::get_width()
{
    return width_;
}

double Character::get_height()
{
    return height_;
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
    Vector translation = position_ - position;
    Translate(translation, false);
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

void Character::Translate(double dx, double dy, bool translate_position)
{
    Vector translation(2);
    translation[0] = dx;
    translation[1] = dy;
    Translate(translation, translate_position);
}

void Character::Translate(math::Vector &translation, bool translate_position)
{
    shape_.Translate(translation);
    head_.Translate(translation);
    body_.Translate(translation);
    outline_.Translate(translation);
    left_arm_.Translate(translation);
    left_thig_.Translate(translation);
    left_calf_.Translate(translation);
    right_arm_.Translate(translation);
    right_thig_.Translate(translation);
    right_calf_.Translate(translation);

    if (translate_position)
        position_ += translation;
}

void Character::WalkAnimationArms(double delta_time, Direction direction)
{
}

void Character::WalkAnimationLegs(double delta_time, physic::Direction direction)
{
    cout << "Animating leg" << endl;
}