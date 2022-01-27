#include "./walking_left_state.hpp"

#include "../character.hpp"
#include "../../../../math/vector.hpp"
#include "../../../../physics/rigid_body.hpp"
#include "../../../../physics/direction.hpp"
#include "../../../../physics/icollidable.hpp"

using graphics::elements::state::BaseState;
using graphics::elements::state::Character;
using graphics::elements::state::WalkingLeftState;
using graphics::elements::state::WalkingRightState;
using math::Vector;
using physic::Direction;
using physic::ICollidable;
using physic::RigidBody;

WalkingLeftState::WalkingLeftState(WalkingLeftState &state)
    : BaseState(state)
{
    name_ = "WalkingLeftState";
}

WalkingLeftState::WalkingLeftState(Character *character)
    : BaseState(character)
{
    character->velocity_[0] = -Character::default_horizontal_velocity_;
    character->velocity_[1] = 0;

    character->acceleration_ = Vector::Zero(2);
    character->external_force_ = character->get_weight() * -1;

    name_ = "WalkingLeftState";
}

BaseState *WalkingLeftState::Clone()
{
    return new WalkingLeftState(*this);
}

void WalkingLeftState::Jump(double delta_time)
{
    // Switch to jumping state
}

void WalkingLeftState::Jump(double delta_time, physic::Direction direction)
{
    if (direction == Direction::kLeft)
        character_->set_state(new JumpingLeftState(character_));
}

void WalkingLeftState::Stop(double delta_time)
{
    character_->set_state(new GroundedState(character_));
}

void WalkingLeftState::Move(double delta_time, Direction direction)
{
    //TODO: if direction is different than current direction then mirror the character
    if (direction == Direction::kRight)
        character_->set_state(new WalkingRightState(character_));
    else
    {
        character_->ProcessMove(delta_time);
    }
}

#include <iostream>
using namespace std;

void WalkingLeftState::ProcessCollision(ICollidable *collidable)
{
    double collidable_x = collidable->get_position()[0] + collidable->get_width();
    double character_x = character_->get_position()[0];

    Vector translate = Vector::Zero(2);
    translate[0] = collidable_x - character_x;

    character_->shape_.Translate(translate);
    character_->position_ += translate;

    character_->set_state(new GroundedState(character_));
}