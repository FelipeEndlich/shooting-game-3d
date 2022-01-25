#include "./walkingRightState.hpp"
#include "../character.hpp"

using namespace graphics::elements::character;

WalkingRightState::WalkingRightState(WalkingRightState &state)
    : State(state)
{
    name = "WalkingRightState";
}

WalkingRightState::WalkingRightState(Character *character)
    : State(character)
{
    character->velocity[0] = 0;
    character->velocity[1] = 0;

    character->acceleration[0] = 0;
    character->acceleration[1] = 0;

    name = "WalkingRightState";
}

State *WalkingRightState::clone()
{
    return new WalkingRightState(*this);
}

void WalkingRightState::fall()
{
}

void WalkingRightState::jump()
{
    // Switch to jumping state
}

void WalkingRightState::stop()
{
    character->setState(new GroundedState(character));
}

void WalkingRightState::move(Direction direction)
{
    //TODO: if direction is different than current direction then mirror the character
    if (direction == Direction::LEFT)
        character->setState(new WalkingLeftState(character));
}