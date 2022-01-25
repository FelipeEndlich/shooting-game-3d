#include "./groundedState.hpp"
#include "./walkingLeftState.hpp"
#include "./walkingRightState.hpp"
#include "../character.hpp"

using namespace graphics::elements::character;

#include <iostream>
using namespace std;
GroundedState::GroundedState(GroundedState &state)
    : State(state)
{
    name = "GroundedState";
}

GroundedState::GroundedState(Character *character)
    : State(character)
{
    character->velocity[0] = 0;
    character->velocity[1] = 0;

    character->acceleration[0] = 0;
    character->acceleration[1] = 0;

    name = "GroundedState";
}

GroundedState::~GroundedState()
{
}

State *GroundedState::clone()
{
    return new GroundedState(*this);
}

void GroundedState::fall()
{
}

void GroundedState::jump()
{
    // Switch to jumping state
}

void GroundedState::stop()
{
}

void GroundedState::move(Direction direction)
{
    //TODO: if direction is different than current direction then mirror the character

    if (direction == Direction::LEFT)
        character->setState(new WalkingLeftState(character));
    else
        character->setState(new WalkingRightState(character));
}