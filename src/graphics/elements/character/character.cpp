#include "./character.hpp"

#include <iostream>
#include <cmath>

#include "./state/falling_state.hpp"
#include "../../../physics/rigid_body.hpp"
#include "../../shapes/circle.hpp"
#include "../../shapes/cuboid.hpp"
#include "../../color/rgba_factory.hpp"
#include "../gun.hpp"
#include "../bullet.hpp"

using ::graphics::color::RGBA;
using ::graphics::elements::Bullet;
using ::graphics::elements::Gun;
using ::graphics::elements::character::BaseState;
using ::graphics::elements::character::Character;
using ::graphics::elements::character::FallingState;
using ::graphics::shapes::Circle;
using ::graphics::shapes::Cuboid;
using ::math::Vector;
using ::physic::Direction;
using ::physic::ICollidable;
using ::std::cout;
using ::std::endl;

Character::Character(bool collision_processable)
    : RigidBody(3)
{
    collision_processable_ = collision_processable;
    Allocate();
}

Character::Character(Vector &initial_position, double radius, RGBA &color, bool collision_processable)
    : RigidBody(3)
{
    collision_processable_ = collision_processable;
    position_ = initial_position;

    position_ += Vector::ThreeDimPoint(-radius / 2, 0, -radius / 2);
    shape_ = Cuboid(position_, radius, radius, radius, color);

    double time_jump_max = 1000;
    Vector gravity_acceleration = Vector::Zero(3);
    gravity_acceleration[1] = 12 * radius / (time_jump_max * time_jump_max);
    set_gravity_acceleration(gravity_acceleration);

    initial_jump_velocity_ = gravity_acceleration * time_jump_max * -1;

    InstantiateCharacter(radius, color);
    Vector gun_initial_position = torso_->get_center_position();
    gun_ = new Gun(gun_initial_position, torso_->get_height(), head_->get_height(), torso_->get_depth());

    Allocate();
}

Character::~Character()
{
    // Deallocate();
}

void Character::InstantiateCharacter(double radius, graphics::color::RGBA &color)
{
    // Radius factors
    double head_width_factor = 0.35;
    double head_height_factor = 0.35;
    double head_depth_factor = 0.35;

    // Height factors
    double body_height_factor = 0.7;
    double leg_height_factor = 0.35;
    double arm_height_factor = 0.7;

    // Width factors
    double body_width_factor = 0.20;
    double leg_width_factor = 0.15;
    double arm_width_factor = 0.15;

    // Rotate factors
    //double arm_rotate_factor = M_PI / 6;
    //double leg_rotate_factor = M_PI / 12;

    // Instantiate head
    double head_width = radius * head_width_factor;
    double head_height = radius * head_height_factor;
    double head_depth = radius * head_depth_factor;
    Vector head_position = position_;
    head_position[0] += head_width / 2;
    head_ = new Head(head_position, head_width_factor, head_height, head_depth, color);

    // Instantiate body
    double body_width = radius * body_width_factor;
    double body_height = radius * body_height_factor;
    double body_depth = radius * body_width_factor;
    Vector body_position = head_->TorsoAnchorPoint();
    body_position[0] -= body_width / 2;
    torso_ = new Torso(body_position, body_width, body_height, body_depth, color);

    // Instantiate left arm
    double left_arm_width = radius * arm_width_factor;
    double left_arm_height = radius * arm_height_factor;
    double left_arm_depth = radius * arm_width_factor;
    Vector left_arm_position = torso_->LeftArmAnchorPoint();
    left_arm_position[0] -= left_arm_width / 2;
    left_arm_ = new Arm(left_arm_position, left_arm_width, left_arm_height, left_arm_depth, color);

    // Instantiate left leg
    double left_thig_width = radius * leg_width_factor;
    double left_thig_height = radius * leg_height_factor;
    double left_thig_depth = radius * leg_width_factor;
    Vector left_thig_position = body_position;
    left_thig_position[0] += (body_width - left_thig_width) / 2;
    left_thig_position[1] += body_height;
    left_thig_ = new Thig(left_thig_position, left_thig_width, left_thig_height, left_thig_depth, color);

    double left_calf_width = radius * leg_width_factor;
    double left_calf_height = radius * leg_height_factor;
    double left_calf_depth = radius * leg_width_factor;
    Vector left_calf_position = left_thig_position;
    left_calf_position[1] += left_thig_height;
    left_calf_ = new Calf(left_calf_position, left_calf_width, left_calf_height, left_calf_depth, color);

    // Instantiate right arm
    double right_arm_width = radius * arm_width_factor;
    double right_arm_height = radius * arm_height_factor;
    double right_arm_depth = radius * arm_width_factor;
    Vector right_arm_position = body_position;
    right_arm_position[0] += (body_width - right_arm_width) / 2;
    right_arm_ = new Arm(right_arm_position, right_arm_width, right_arm_height, right_arm_depth, color);

    // Instantiate right leg
    double right_thig_width = radius * leg_width_factor;
    double right_thig_height = radius * leg_height_factor;
    double right_thig_depth = radius * leg_width_factor;
    Vector right_thig_position = body_position;
    right_thig_position[0] += (body_width - right_thig_width) / 2;
    right_thig_position[1] += body_height;
    right_thig_ = new Thig(right_thig_position, right_thig_width, right_thig_height, right_thig_depth, color);

    double right_calf_width = radius * leg_width_factor;
    double right_calf_height = radius * leg_height_factor;
    double right_calf_depth = radius * leg_width_factor;
    Vector right_calf_position = right_thig_position;
    right_calf_position[1] += right_thig_height;
    right_calf_ = new Calf(right_calf_position, right_calf_width, right_calf_height, right_calf_depth, color);

    left_arm_->Rotate(left_arm_->TorsoAnchorPoint(), -0.80);
    right_arm_->Rotate(right_arm_->TorsoAnchorPoint(), -0.20);

    // Set characters width and height
    width_ = body_width;
    height_ = radius * 2;

    // outline_ = new Cuboid(get_position(), get_width(), get_height(), color::RGBAFactory::get_color("black"));
    outline_ = new Circle(left_arm_->TorsoAnchorPoint(), 0.3, color::RGBAFactory::get_color("red"));
}

Character &Character::operator=(const Character &other)
{
    if (this != &other)
    {
        position_ = other.position_;
        shape_ = other.shape_;
        head_ = other.head_;
        torso_ = other.torso_;
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
        looking_right_ = other.looking_right_;

        //Deallocate();
        this->state_ = other.state_->Clone();
    }
    return *this;
}

void Character::Render()
{
    // shape_.Draw();
    head_->Draw();
    // torso_->Draw();

    // if (looking_right_)
    // {
    //     left_arm_->Draw();
    //     gun_->Render();
    //     right_arm_->Draw();
    // }
    // else
    // {
    //     right_arm_->Draw();
    //     gun_->Render();
    //     left_arm_->Draw();
    // }

    // right_thig_->Draw();
    // right_calf_->Draw();

    // left_thig_->Draw();
    // left_calf_->Draw();
}

void Character::Jump(double delta_time)
{
    // state_->Jump(delta_time);
}

void Character::Jump(double delta_time, physic::Direction direction)
{
    // state_->Jump(delta_time, direction);
}

void Character::Stop(double delta_time)
{
    // state_->Stop(delta_time);
}

void Character::Move(double delta_time, Direction direction)
{
    // state_->Move(delta_time, direction);
}

void Character::set_state(BaseState *state)
{
    // delete state_;
    // this->state_ = state;
}

void Character::Aim(double angle)
{
    /*
    if (looking_right_)
    {

        double increment = angle - gun_->get_angle();
        Vector position = left_arm_->TorsoAnchorPoint();

        left_arm_->Rotate(position, increment);
        right_arm_->Rotate(position, increment);
        gun_->Rotate(position, increment);
    }
    else
    {
        double increment = angle - gun_->get_angle();
        Vector position = left_arm_->TorsoAnchorPoint();

        left_arm_->Rotate(position, increment);
        right_arm_->Rotate(position, increment);
        gun_->Rotate(position, increment);
    }
    */
}

void Character::Allocate()
{
    // graphics::shapes::Cuboid left_arm_;
    // state_ = new FallingState(this);
}

void Character::Deallocate()
{
    /*
    delete state_;
    delete head_;
    delete torso_;
    delete left_arm_;
    delete right_arm_;
    delete left_thig_;
    delete right_thig_;
    delete left_calf_;
    delete right_calf_;
    delete gun_;
    delete outline_;
    */
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

bool Character::IsLookingRight()
{
    return looking_right_;
}

void Character::ProcessCollision(ICollidable *collidable)
{
    /*
    if (collision_processable_)
    {
        state_->ProcessCollision(collidable);
    }
    */
}

void Character::ProcessMove(double delta_time)
{
    /*
    Vector position = position_;
    Update(delta_time);
    Vector translation = position_ - position;
    Translate(translation, false);
    */
}

void Character::ProcessCollisionByLeft(ICollidable *collidable)
{
    /*
    double collidable_x = collidable->get_position()[0] + collidable->get_width();
    double character_x = get_position()[0];
    Translate(collidable_x - character_x, 0);
    */
}

void Character::ProcessCollisionByRight(ICollidable *collidable)
{
    /*
    double collidable_x = collidable->get_position()[0];
    double character_x = get_position()[0] + get_width();
    Translate(collidable_x - character_x, 0);
    */
}

void Character::ProcessCollisionByTop(ICollidable *collidable)
{
    /*
    double collidable_y = collidable->get_position()[1] + collidable->get_height();
    double character_y = get_position()[1];
    Translate(0, collidable_y - character_y);
    */
}

void Character::ProcessCollisionByBottom(ICollidable *collidable)
{
    /*
    double collidable_y = collidable->get_position()[1];
    double character_y = get_position()[1] + get_height();
    Translate(0, collidable_y - character_y);
    */
}

void Character::ProcessGravity()
{
    //state_->ProcessGravity();
}

void Character::Translate(double dx, double dy, bool translate_position)
{
    /*
    Vector translation(2);
    translation[0] = dx;
    translation[1] = dy;
    Translate(translation, translate_position);
    */
}

void Character::Translate(math::Vector &translation, bool translate_position)
{ /*
  shape_.Translate(translation);
  head_->Translate(translation);
  torso_->Translate(translation);
  outline_->Translate(translation);
  left_arm_->Translate(translation);
  right_arm_->Translate(translation);
  left_thig_->Translate(translation);
  right_thig_->Translate(translation);
  left_calf_->Translate(translation);
  right_calf_->Translate(translation);

  gun_->Translate(translation, translate_position);

  if (translate_position)
      position_ += translation;
  */
}

void Character::ResetAnimation()
{
    /*
    head_->Rotate(head_->get_center_position(), -head_->get_angle());

    torso_->Rotate(torso_->get_center_position(), -torso_->get_angle());
    Vector torso_translation = head_->TorsoAnchorPoint() - torso_->HeadAnchorPoint();
    torso_->Translate(torso_translation);

    right_arm_->Rotate(right_arm_->get_center_position(), -right_arm_->get_angle());
    Vector right_arm_translation = torso_->RightArmAnchorPoint() - right_arm_->TorsoAnchorPoint();
    right_arm_->Translate(right_arm_translation);

    left_thig_->Rotate(left_thig_->get_center_position(), -left_thig_->get_angle());
    Vector left_thig_translation = torso_->LeftThigAnchorPoint() - left_thig_->TorsoAnchorPoint();
    left_thig_->Translate(left_thig_translation);

    right_thig_->Rotate(right_thig_->get_center_position(), -right_thig_->get_angle());
    Vector right_thig_translation = torso_->RightThigAnchorPoint() - right_thig_->TorsoAnchorPoint();
    right_thig_->Translate(right_thig_translation);

    left_calf_->Rotate(left_calf_->get_center_position(), -left_calf_->get_angle());
    Vector left_calf_translation = left_thig_->CalfAnchorPoint() - left_calf_->ThigAnchorPoint();
    left_calf_->Translate(left_calf_translation);

    right_calf_->Rotate(right_calf_->get_center_position(), -right_calf_->get_angle());
    Vector right_calf_translation = right_thig_->CalfAnchorPoint() - right_calf_->ThigAnchorPoint();
    right_calf_->Translate(right_calf_translation);

    left_arm_->Rotate(left_arm_->get_center_position(), -left_arm_->get_angle());
    Vector left_arm_translation = torso_->LeftArmAnchorPoint() - left_arm_->TorsoAnchorPoint();
    left_arm_->Translate(left_arm_translation);

    gun_->Rotate(torso_->LeftArmAnchorPoint(), -gun_->get_angle());

    if (looking_right_)
    {
        left_arm_->Rotate(left_arm_->TorsoAnchorPoint(), -0.80);
        right_arm_->Rotate(right_arm_->TorsoAnchorPoint(), -0.20);
    }
    else
    {
        right_arm_->Rotate(right_arm_->TorsoAnchorPoint(), 0.80);
        left_arm_->Rotate(left_arm_->TorsoAnchorPoint(), 0.20);
    }
    */
}

void Character::Mirror()
{
    /*
    Vector center = torso_->get_center_position();

    outline_->Scale(center, -1, 1);
    // shape_.Scale(center, -1, 1);

    head_->Mirror(center);
    torso_->Mirror(center);
    left_arm_->Mirror(center);
    right_arm_->Mirror(center);
    left_thig_->Mirror(center);
    right_thig_->Mirror(center);
    left_calf_->Mirror(center);
    right_calf_->Mirror(center);
    gun_->Mirror(center);

    looking_right_ = !looking_right_;
    */
}

Bullet *Character::Shoot()
{
    return gun_->Shoot(!looking_right_);
}