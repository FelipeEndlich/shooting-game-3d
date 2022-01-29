#include "./falling_left_state.hpp"

#include "../character.hpp"
#include "./grounded_state.hpp"
#include "../../../../math/vector.hpp"
#include "../../../../physics/direction.hpp"
#include "../../../../physics/icollidable.hpp"
#include "../../../../physics/rigid_body.hpp"

using graphics::elements::character::BaseState;
using graphics::elements::character::Character;
using graphics::elements::character::FallingLeftState;
using graphics::elements::character::FallingState;
using graphics::elements::character::GroundedState;
using math::Vector;
using physic::Direction;
using physic::ICollidable;
using physic::RigidBody;

FallingLeftState::FallingLeftState(FallingLeftState &state)
    : BaseState(state)
{
    name_ = "FallingLeftState";
}

FallingLeftState::FallingLeftState(Character *character)
    : BaseState(character)
{
    character->velocity_[0] = -Character::default_horizontal_velocity_;
    if (character->velocity_[1] < 0)
        character->velocity_[1] = 0;

    character->acceleration_ = Vector::Zero(2);
    character->external_force_ = Vector::Zero(2);

    name_ = "FallingLeftState";
}

BaseState *FallingLeftState::Clone()
{
    return new FallingLeftState(*this);
}

void FallingLeftState::Jump(double delta_time)
{
    character_->set_state(new FallingState(character_));
}

void FallingLeftState::Jump(double delta_time, physic::Direction direction)
{
    if (direction == Direction::kLeft)
        character_->ProcessMove(delta_time);
    else
        character_->set_state(new FallingRightState(character_));
}

void FallingLeftState::Stop(double delta_time)
{
    character_->set_state(new FallingState(character_));
}

void FallingLeftState::Move(double delta_time, Direction direction)
{
    if (direction == Direction::kLeft)
        character_->ProcessMove(delta_time);
    else
        character_->set_state(new FallingRightState(character_));
}

void FallingLeftState::ProcessCollision(ICollidable *collidable)
{
    if (collidable->IsColliding(character_->get_last_position()[0], character_->get_position()[1], character_->get_width(), character_->get_height()))
    {
        character_->ProcessCollisionByBottom(collidable);
        character_->set_state(new GroundedState(character_));
    }
    else
    {
        character_->ProcessCollisionByLeft(collidable);
        character_->set_state(new FallingState(character_));
    }
}