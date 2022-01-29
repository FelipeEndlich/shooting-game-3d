#include "./walking_right_state.hpp"

#include <cmath>

#include "../character.hpp"
#include "walk_phase.hpp"
#include "../../../../math/vector.hpp"
#include "../../../../physics/rigid_body.hpp"
#include "../../../../physics/direction.hpp"
#include "../../../../physics/icollidable.hpp"

using graphics::elements::character::BaseState;
using graphics::elements::character::Character;
using graphics::elements::character::WalkingLeftState;
using graphics::elements::character::WalkingRightState;
using graphics::elements::character::WalkPhase;
using math::Vector;
using physic::Direction;
using physic::ICollidable;
using physic::RigidBody;

#include <iostream>
using namespace std;

WalkingRightState::WalkingRightState(WalkingRightState &state)
    : BaseState(state)
{
    name_ = "WalkingRightState";

    phase_ = WalkPhase::kPassing;
}

WalkingRightState::WalkingRightState(Character *character)
    : BaseState(character)
{
    character->velocity_[0] = Character::default_horizontal_velocity_;
    character->velocity_[1] = 0;

    character->acceleration_ = Vector::Zero(2);
    character->external_force_ = character->get_weight() * -1;

    phase_ = WalkPhase::kPassing;

    name_ = "WalkingRightState";
}

BaseState *WalkingRightState::Clone()
{
    return new WalkingRightState(*this);
}

void WalkingRightState::Jump(double delta_time, physic::Direction direction)
{
    if (direction == Direction::kRight)
        character_->set_state(new JumpingRightState(character_));
}

void WalkingRightState::Stop(double delta_time)
{
    character_->set_state(new GroundedState(character_));
}

void WalkingRightState::Move(double delta_time, Direction direction)
{
    //TODO: if direction is different than current direction then mirror the character
    if (direction == Direction::kLeft)
        character_->set_state(new WalkingLeftState(character_));
    else
    {
        character_->ProcessMove(delta_time);
        Animate();
    }
}

void WalkingRightState::ProcessCollision(ICollidable *collidable)
{
    character_->ProcessCollisionByRight(collidable);
    character_->set_state(new GroundedState(character_));
}

void WalkingRightState::ProcessGravity()
{
    character_->set_state(new FallingRightState(character_));
}

void WalkingRightState::Animate()
{
    if (phase_ == WalkPhase::kContact)
    {
    }
    else if (phase_ == WalkPhase::kDown)
    {
    }
    else if (phase_ == WalkPhase::kPassing)
    {
        double leg_rotation_angle = M_PI / 24;

        
    }
    else if (phase_ == WalkPhase::kUp)
    {
    }
    else if (phase_ == WalkPhase::kAir)
    {
    }
}

void WalkingRightState::ResetAnimation()
{
    // double left_arm_angle = character_->left_arm_.get_angle();
    // double right_arm_angle = character_->right_arm_.get_angle();
    // double left_leg_angle = character_->left_thig_.get_angle();
    // double right_leg_angle = character_->right_thig_.get_angle();
}