#include "./walking_right_state.hpp"

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

WalkingRightState::WalkingRightState(WalkingRightState &state)
    : BaseState(state)
{
    name_ = "WalkingRightState";
}

WalkingRightState::WalkingRightState(Character *character)
    : BaseState(character)
{
    character->velocity_[0] = RigidBody::default_horizontal_velocity_;
    character->velocity_[1] = 0;

    character->acceleration_[0] = 0;
    character->acceleration_[1] = 0;

    name_ = "WalkingRightState";
}

BaseState *WalkingRightState::Clone()
{
    return new WalkingRightState(*this);
}

void WalkingRightState::Fall(double delta_time)
{
}

void WalkingRightState::Jump(double delta_time)
{
    // Switch to jumping state
}

void WalkingRightState::Stop(double delta_time)
{
    character_->set_state(new GroundedState(character_));
}

void WalkingRightState::Move(double delta_time, Direction direction)
{
    //TODO: if direction is different than current direction then mirror the character
    if (direction == Direction::kLeft)
        character_->set_state(new WalkingLeftState(character_));
    else
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
}

#include <iostream>
using namespace std;

void WalkingRightState::ProcessCollision(ICollidable *collidable)
{
    double collidable_x = collidable->get_position()[0];
    double character_x = character_->get_position()[0] + character_->get_width();

    Vector translate = Vector::Zero(2);
    translate[0] = collidable_x - character_x;

    character_->shape_.Translate(translate);
    character_->position_ += translate;

    character_->set_state(new GroundedState(character_));
}