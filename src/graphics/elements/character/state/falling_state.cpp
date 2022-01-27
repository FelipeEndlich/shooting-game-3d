#include "./falling_state.hpp"

#include "../character.hpp"
#include "./grounded_state.hpp"
#include "../../../../math/vector.hpp"
#include "../../../../physics/direction.hpp"
#include "../../../../physics/icollidable.hpp"
#include "../../../../physics/rigid_body.hpp"

using graphics::elements::state::BaseState;
using graphics::elements::state::Character;
using graphics::elements::state::FallingState;
using graphics::elements::state::GroundedState;
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
    character->velocity_ = Vector::Zero(2);
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

void FallingState::Stop(double delta_time)
{
    character_->ProcessMove(delta_time);
}

void FallingState::Move(double delta_time, Direction direction)
{
}

#include <iostream>
using namespace std;

void FallingState::ProcessCollision(ICollidable *collidable)
{
    double collidable_y = collidable->get_position()[1];
    double character_y = character_->get_position()[1] + character_->get_height();

    Vector translate = Vector::Zero(2);
    translate[1] = collidable_y - character_y;

    character_->shape_.Translate(translate);
    character_->position_ += translate;

    character_->set_state(new GroundedState(character_));
}