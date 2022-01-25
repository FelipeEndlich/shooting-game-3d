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
    character->velocity[1] = -1;

    character->acceleration[0] = 0;
    character->acceleration[1] = 0;

    name = "WalkingLeftState";
}

State *WalkingLeftState::clone()
{
    return new WalkingLeftState(*this);
}

void WalkingLeftState::fall(double deltaTime)
{
}

void WalkingLeftState::jump(double deltaTime)
{
    // Switch to jumping state
}

void WalkingLeftState::stop(double deltaTime)
{
    character->setState(new GroundedState(character));
}

void WalkingLeftState::move(double deltaTime, Direction direction)
{
    //TODO: if direction is different than current direction then mirror the character
    if (direction == Direction::RIGHT)
        character->setState(new WalkingRightState(character));
}