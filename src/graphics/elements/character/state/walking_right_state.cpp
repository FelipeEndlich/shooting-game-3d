#include "./walking_right_state.hpp"

#include "../character.hpp"
#include "../../../../math/vector.hpp"
#include "../../../../physics/rigidBody.hpp"

using graphics::elements::state::BaseState;
using graphics::elements::state::Character;
using graphics::elements::state::Direction;
using graphics::elements::state::WalkingLeftState;
using graphics::elements::state::WalkingRightState;
using math::Vector;
using physic::RigidBody;

WalkingRightState::WalkingRightState(WalkingRightState &state)
    : BaseState(state)
{
    name_ = "WalkingRightState";
}

WalkingRightState::WalkingRightState(Character *character)
    : BaseState(character)
{
    character->velocity[0] = RigidBody::DEFAULT_HORIZONTAL_VELOCITY;
    character->velocity[1] = 0;

    character->acceleration[0] = 0;
    character->acceleration[1] = 0;

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
        double x = character_->position[0];
        double y = character_->position[1];

        character_->update(delta_time);

        double dx = character_->position[0] - x;
        double dy = character_->position[1] - y;

        Vector translate = Vector(2);
        translate[0] = dx;
        translate[1] = dy;

        character_->shape_.translate(translate);
    }
}