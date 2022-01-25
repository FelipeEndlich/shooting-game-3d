#include "./walkingRightState.hpp"
#include "../character.hpp"
#include "../../../../math/vector.hpp"
#include "../../../../physics/rigidBody.hpp"

using namespace math;
using namespace physics;
using namespace graphics::elements::character;

WalkingRightState::WalkingRightState(WalkingRightState &state)
    : State(state)
{
    name = "WalkingRightState";
}

WalkingRightState::WalkingRightState(Character *character)
    : State(character)
{
    character->velocity[0] = RigidBody::DEFAULT_HORIZONTAL_VELOCITY;
    character->velocity[1] = 0;

    character->acceleration[0] = 0;
    character->acceleration[1] = 0;

    name = "WalkingRightState";
}

State *WalkingRightState::clone()
{
    return new WalkingRightState(*this);
}

void WalkingRightState::fall(double deltaTime)
{
}

void WalkingRightState::jump(double deltaTime)
{
    // Switch to jumping state
}

void WalkingRightState::stop(double deltaTime)
{
    character->setState(new GroundedState(character));
}

#include <iostream>
using namespace std;
void WalkingRightState::move(double deltaTime, Direction direction)
{
    //TODO: if direction is different than current direction then mirror the character
    if (direction == Direction::LEFT)
        character->setState(new WalkingLeftState(character));
    else
    {
        double x = character->position[0];
        double y = character->position[1];

        character->update(deltaTime);

        double dx = character->position[0] - x;
        double dy = character->position[1] - y;

        Vector translate = Vector(2);
        translate[0] = dx;
        translate[1] = dy;

        character->shape.translate(translate);
    }
}