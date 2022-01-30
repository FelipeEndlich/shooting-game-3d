#include "./walking_left_state.hpp"

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

WalkingLeftState::WalkingLeftState(WalkingLeftState &state)
    : BaseState(state)
{
    name_ = "WalkingLeftState";
    character_ = state.character_;
    animation_system_ = state.animation_system_;
}

WalkingLeftState::WalkingLeftState(Character *character)
    : BaseState(character)
{
    character->velocity_[0] = -Character::default_horizontal_velocity_;
    character->velocity_[1] = 0;

    character->acceleration_ = Vector::Zero(2);
    character->external_force_ = character->get_weight() * -1;

    name_ = "WalkingLeftState";

    character_->ResetAnimation();
    animation_system_ = WalkingAnimationSystem(character_);
}

BaseState *WalkingLeftState::Clone()
{
    return new WalkingLeftState(*this);
}

void WalkingLeftState::Jump(double delta_time, physic::Direction direction)
{
    if (direction == Direction::kLeft)
    {
        character_->ResetAnimation();
        character_->set_state(new JumpingLeftState(character_));
    }
}

void WalkingLeftState::Stop(double delta_time)
{
    character_->ResetAnimation();
    character_->set_state(new GroundedState(character_));
}

void WalkingLeftState::Move(double delta_time, Direction direction)
{
    if (direction == Direction::kRight)
    {
        character_->looking_right_ = true;
        character_->ResetAnimation();
        character_->Mirror();
        character_->set_state(new WalkingRightState(character_));
    }
    else
    {
        character_->ProcessMove(delta_time);
        Animate();
    }
}

void WalkingLeftState::ProcessCollision(ICollidable *collidable)
{
    character_->ProcessCollisionByLeft(collidable);
    character_->ResetAnimation();
    character_->set_state(new GroundedState(character_));
}

void WalkingLeftState::ProcessGravity()
{
    character_->ResetAnimation();
    character_->set_state(new FallingLeftState(character_));
}

void WalkingLeftState::Animate()
{
    animation_system_.Animate();
}