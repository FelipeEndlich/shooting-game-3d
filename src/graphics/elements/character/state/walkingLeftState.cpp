#include "./walkingLeftState.hpp"
#include "../character.hpp"

using namespace graphics::elements::character;

#include <iostream>
using namespace std;
WalkingLeftState::WalkingLeftState(WalkingLeftState &state)
    : State(state)
{
    name = "WalkingLeftState";
}

WalkingLeftState::WalkingLeftState(Character *character)
    : State(character)
{
    character->velocity[0] = 0;
    character->velocity[1] = 0;

    character->acceleration[0] = 0;
    character->acceleration[1] = 0;

    name = "WalkingLeftState";
}

State *WalkingLeftState::clone()
{
    return new WalkingLeftState(*this);
}

void WalkingLeftState::fall()
{
}

void WalkingLeftState::jump()
{
    // Switch to jumping state
}

void WalkingLeftState::stop()
{
    character->setState(new GroundedState(character));
}

void WalkingLeftState::move(Direction direction)
{
    //TODO: if direction is different than current direction then mirror the character
    if (direction == Direction::RIGHT)
        character->setState(new WalkingRightState(character));
}