#include "./walkingLeftState.hpp"
#include "../character.hpp"
#include "../../../../math/vector.hpp"
#include "../../../../physics/rigidBody.hpp"

using namespace math;
using namespace physics;
using namespace graphics::elements::character;

WalkingLeftState::WalkingLeftState(WalkingLeftState &state)
    : State(state)
{
    name = "WalkingLeftState";
}

WalkingLeftState::WalkingLeftState(Character *character)
    : State(character)
{
    character->velocity[0] = -RigidBody::DEFAULT_HORIZONTAL_VELOCITY;
    character->velocity[1] = 0;

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