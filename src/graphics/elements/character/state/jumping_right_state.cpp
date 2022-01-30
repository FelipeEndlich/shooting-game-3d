#include "./jumping_right_state.hpp"

#include "../character.hpp"
#include "./grounded_state.hpp"
#include "./falling_right_state.hpp"
#include "../../../../math/vector.hpp"
#include "../../../../physics/direction.hpp"
#include "../../../../physics/icollidable.hpp"
#include "../../../../physics/rigid_body.hpp"

using graphics::elements::character::BaseState;
using graphics::elements::character::Character;
using graphics::elements::character::FallingRightState;
using graphics::elements::character::GroundedState;
using graphics::elements::character::JumpingRightState;
using math::Vector;
using physic::Direction;
using physic::ICollidable;
using physic::RigidBody;

JumpingRightState::JumpingRightState(JumpingRightState &state)
    : BaseState(state)
{
    name_ = "JumpingRightState";
}

JumpingRightState::JumpingRightState(Character *character)
    : BaseState(character)
{
    if (character->velocity_[1] == 0)
        character->velocity_ = character_->initial_jump_velocity_;
    character->velocity_[0] = Character::default_horizontal_velocity_;

    character->acceleration_ = Vector::Zero(2);
    character->external_force_ = Vector::Zero(2);

    name_ = "JumpingRightState";
}

BaseState *JumpingRightState::Clone()
{
    return new JumpingRightState(*this);
}

void JumpingRightState::Jump(double delta_time)
{
    character_->set_state(new JumpingState(character_));
}

void JumpingRightState::Jump(double delta_time, physic::Direction direction)
{
    if (character_->velocity_[1] > 0)
        character_->set_state(new FallingRightState(character_));
    else if (direction == Direction::kRight)
        character_->ProcessMove(delta_time);
    else
    {
        character_->Mirror();
        character_->set_state(new JumpingLeftState(character_));
    }
}

void JumpingRightState::Stop(double delta_time)
{
    character_->set_state(new FallingState(character_));
}

void JumpingRightState::Move(double delta_time, Direction direction)
{
    if (direction == Direction::kRight)
        character_->set_state(new FallingRightState(character_));
    else
    {
        character_->Mirror();
        character_->set_state(new FallingLeftState(character_));
    }
}

void JumpingRightState::ProcessCollision(ICollidable *collidable)
{
    if (collidable->IsColliding(character_->get_last_position()[0], character_->get_position()[1], 0, character_->get_height()))
    {
        character_->ProcessCollisionByTop(collidable);
        character_->set_state(new FallingState(character_));
    }
    else
    {
        character_->ProcessCollisionByRight(collidable);
        character_->set_state(new JumpingState(character_));
    }
}