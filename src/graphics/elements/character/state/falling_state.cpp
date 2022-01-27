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
    character->velocity_[0] = 0;
    character->velocity_[1] = 0;

    character->acceleration_[0] = 0;
    character->acceleration_[1] = 0;

    character->external_force_[0] = 0;
    character->external_force_[1] = 0;

    name_ = "FallingState";
}

BaseState *FallingState::Clone()
{
    return new FallingState(*this);
}

void FallingState::Fall(double delta_time)
{
    FallUpdate(delta_time);
}

void FallingState::Jump(double delta_time)
{
    FallUpdate(delta_time);
}

void FallingState::Stop(double delta_time)
{
    FallUpdate(delta_time);
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

void FallingState::FallUpdate(double delta_time)
{
    double x = character_->position_[0];
    double y = character_->position_[1];

    character_->Update(delta_time);

    double dx = character_->position_[0] - x;
    double dy = character_->position_[1] - y;

    Vector translate = Vector(2);
    translate[0] = dx;
    translate[1] = dy;

    character_->shape_.Translate(translate);
}