#include "./grounded_state.hpp"

#include "../character.hpp"
#include "./walking_left_state.hpp"
#include "./walking_right_state.hpp"
#include "../../../../physics/direction.hpp"

using graphics::elements::state::BaseState;
using graphics::elements::state::Character;
using graphics::elements::state::GroundedState;
using physic::Direction;

GroundedState::GroundedState(GroundedState &state)
    : BaseState(state)
{
    name_ = "GroundedState";
}

GroundedState::GroundedState(Character *character)
    : BaseState(character)
{
    character->velocity_[0] = 0;
    character->velocity_[1] = 0;

    character->acceleration_[0] = 0;
    character->acceleration_[1] = 0;

    name_ = "GroundedState";
}

GroundedState::~GroundedState()
{
}

BaseState *GroundedState::Clone()
{
    return new GroundedState(*this);
}

void GroundedState::Fall(double delta_time)
{
}

void GroundedState::Jump(double delta_time)
{
    // Switch to jumping state
}

void GroundedState::Stop(double delta_time)
{
}

void GroundedState::Move(double delta_time, Direction direction)
{
    //TODO: if direction is different than current direction then mirror the character

    if (direction == Direction::kLeft)
        character_->set_state(new WalkingLeftState(character_));
    else
        character_->set_state(new WalkingRightState(character_));
}