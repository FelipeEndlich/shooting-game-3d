#include "./falling_left_state.hpp"

#include "../character.hpp"
#include "./grounded_state.hpp"
#include "../../../../math/vector.hpp"
#include "../../../../physics/direction.hpp"
#include "../../../../physics/icollidable.hpp"
#include "../../../../physics/rigid_body.hpp"

using graphics::elements::state::BaseState;
using graphics::elements::state::Character;
using graphics::elements::state::FallingLeftState;
using graphics::elements::state::FallingState;
using graphics::elements::state::GroundedState;
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

#include <iostream>
using namespace std;

void FallingLeftState::ProcessCollision(ICollidable *collidable)
{
    double collidable_y = collidable->get_position()[1];
    double character_y = character_->get_position()[1] + character_->get_height();

    Vector translate = Vector::Zero(2);
    translate[1] = collidable_y - character_y;

    character_->shape_.Translate(translate);
    character_->position_ += translate;

    character_->set_state(new GroundedState(character_));
}