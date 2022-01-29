#include "./jumping_left_state.hpp"

#include "../character.hpp"
#include "./grounded_state.hpp"
#include "./falling_left_state.hpp"
#include "../../../../math/vector.hpp"
#include "../../../../physics/direction.hpp"
#include "../../../../physics/icollidable.hpp"
#include "../../../../physics/rigid_body.hpp"

using graphics::elements::character::BaseState;
using graphics::elements::character::Character;
using graphics::elements::character::FallingLeftState;
using graphics::elements::character::GroundedState;
using graphics::elements::character::JumpingLeftState;
using math::Vector;
using physic::Direction;
using physic::ICollidable;
using physic::RigidBody;

JumpingLeftState::JumpingLeftState(JumpingLeftState &state)
    : BaseState(state)
{
    name_ = "JumpingLeftState";
}

JumpingLeftState::JumpingLeftState(Character *character)
    : BaseState(character)
{
    if (character->velocity_[1] == 0)
        character->velocity_ = character_->initial_jump_velocity_;
    character->velocity_[0] = -Character::default_horizontal_velocity_;
    character->acceleration_ = Vector::Zero(2);
    character->external_force_ = Vector::Zero(2);

    name_ = "JumpingLeftState";
}

BaseState *JumpingLeftState::Clone()
{
    return new JumpingLeftState(*this);
}

void JumpingLeftState::Jump(double delta_time)
{
    character_->set_state(new JumpingState(character_));
}

void JumpingLeftState::Jump(double delta_time, physic::Direction direction)
{
    if (character_->velocity_[1] > 0)
        character_->set_state(new FallingLeftState(character_));
    else if (direction == Direction::kLeft)
        character_->ProcessMove(delta_time);
    else
        character_->set_state(new JumpingRightState(character_));
}

void JumpingLeftState::Stop(double delta_time)
{
    character_->set_state(new FallingState(character_));
}

void JumpingLeftState::Move(double delta_time, Direction direction)
{
    if (direction == Direction::kLeft)
        character_->set_state(new FallingLeftState(character_));
    else
        character_->set_state(new FallingRightState(character_));
}

void JumpingLeftState::ProcessCollision(ICollidable *collidable)
{
    if (collidable->IsColliding(character_->get_last_position()[0], character_->get_position()[1], character_->get_width(), character_->get_height()))
    {
        character_->ProcessCollisionByTop(collidable);
        character_->set_state(new FallingState(character_));
    }
    else
    {
        character_->ProcessCollisionByLeft(collidable);
        character_->set_state(new JumpingState(character_));
    }
}