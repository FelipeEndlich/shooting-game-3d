#include "./falling_state.hpp"

#include "../character.hpp"
#include "./grounded_state.hpp"
#include "./falling_left_state.hpp"
#include "./falling_right_state.hpp"
#include "../../../../math/vector.hpp"
#include "../../../../physics/direction.hpp"
#include "../../../../physics/icollidable.hpp"
#include "../../../../physics/rigid_body.hpp"

using graphics::elements::character::BaseState;
using graphics::elements::character::Character;
using graphics::elements::character::FallingLeftState;
using graphics::elements::character::FallingRightState;
using graphics::elements::character::FallingState;
using graphics::elements::character::GroundedState;
using math::Vector;
using physic::Direction;
using physic::ICollidable;
using physic::RigidBody;

FallingState::FallingState(FallingState &state)
    : BaseState(state)
{
    name_ = "FallingState";
}

FallingState::FallingState(Character *character)
    : BaseState(character)
{
    character->velocity_[0] = 0;

    if (character->velocity_[1] < 0)
        character->velocity_[1] = 0;

    character->acceleration_ = Vector::Zero(2);
    character->external_force_ = Vector::Zero(2);

    name_ = "FallingState";
}

BaseState *FallingState::Clone()
{
    return new FallingState(*this);
}

void FallingState::Jump(double delta_time)
{
    character_->ProcessMove(delta_time);
}

void FallingState::Jump(double delta_time, physic::Direction direction)
{
    if (direction == Direction::kRight)
    {
        if (!character_->looking_right_)
            character_->Mirror();

        character_->set_state(new FallingRightState(character_));
    }
    else
    {
        if (character_->looking_right_)
            character_->Mirror();

        character_->set_state(new FallingLeftState(character_));
    }
}

void FallingState::Stop(double delta_time)
{
    character_->ProcessMove(delta_time);
}

void FallingState::Move(double delta_time, Direction direction)
{
    if (direction == Direction::kRight)
    {
        if (!character_->looking_right_)
            character_->Mirror();

        character_->set_state(new FallingRightState(character_));
    }
    else
    {
        if (character_->looking_right_)
            character_->Mirror();

        character_->set_state(new FallingLeftState(character_));
    }
}

void FallingState::ProcessCollision(ICollidable *collidable)
{
    character_->ProcessCollisionByBottom(collidable);
    character_->set_state(new GroundedState(character_));
}