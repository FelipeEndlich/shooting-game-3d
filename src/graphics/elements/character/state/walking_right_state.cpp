#include "./walking_right_state.hpp"

#include <cmath>
#include <map>
#include <tuple>

#include "../character.hpp"
#include "../../../../math/vector.hpp"
#include "../../../../physics/rigid_body.hpp"
#include "../../../../physics/direction.hpp"
#include "../../../../physics/icollidable.hpp"
#include "../animation/walking_animation_system.hpp"

using graphics::elements::character::BaseState;
using graphics::elements::character::Character;
using graphics::elements::character::WalkingLeftState;
using graphics::elements::character::WalkingRightState;
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
    character_ = state.character_;
    animation_system_ = state.animation_system_;
}

WalkingRightState::WalkingRightState(Character *character)
    : BaseState(character)
{
    character->velocity_[0] = Character::default_horizontal_velocity_;
    character->velocity_[1] = 0;

    character->acceleration_ = Vector::Zero(2);
    character->external_force_ = character->get_weight() * -1;

    name_ = "WalkingRightState";

    character_->ResetAnimation();
    animation_system_ = WalkingAnimationSystem(character_);
}

BaseState *WalkingRightState::Clone()
{
    return new WalkingRightState(*this);
}

void WalkingRightState::Jump(double delta_time, physic::Direction direction)
{
    if (direction == Direction::kRight)
    {
        character_->ResetAnimation();
        character_->set_state(new JumpingRightState(character_));
    }
}

void WalkingRightState::Stop(double delta_time)
{
    character_->ResetAnimation();
    character_->set_state(new GroundedState(character_));
}

void WalkingRightState::Move(double delta_time, Direction direction)
{
    if (direction == Direction::kLeft)
    {
        character_->looking_right_ = false;
        character_->ResetAnimation();
        character_->Mirror();
        character_->set_state(new WalkingLeftState(character_));
    }
    else
    {
        character_->ProcessMove(delta_time);
        Animate();
    }
}

void WalkingRightState::ProcessCollision(ICollidable *collidable)
{
    character_->ProcessCollisionByRight(collidable);
    character_->ResetAnimation();
    character_->set_state(new GroundedState(character_));
}

void WalkingRightState::ProcessGravity()
{
    character_->ResetAnimation();
    character_->set_state(new FallingRightState(character_));
}

void WalkingRightState::Animate()
{
    animation_system_.Animate();
}