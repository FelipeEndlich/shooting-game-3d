#include "./character.hpp"
#include "./state/grounded_state.hpp"
#include "../../../physics/rigidBody.hpp"

using namespace math;
using namespace graphics::color;
using namespace graphics::shapes;
using namespace graphics::elements::state;

Character::Character()
    : RigidBody(2)
{
    allocate();
}

Character::Character(Vector &initialPosition, double radius, RGBA &color)
    : RigidBody(2)
{
    position = initialPosition;
    shape = Circle(position, radius, color);
    allocate();
}

Character::~Character()
{
    deallocate();
}

Character &Character::operator=(const Character &other)
{
    if (this != &other)
    {
        position = other.position;
        shape = other.shape;
        velocity = other.velocity;
        acceleration = other.acceleration;

        deallocate();
        this->state = other.state->Clone();
    }
    return *this;
}

void Character::render()
{
    shape.draw();
}

void Character::fall(double deltaTime)
{
    state->Fall(deltaTime);
}

void Character::jump(double deltaTime)
{
    state->Jump(deltaTime);
}

void Character::stop(double deltaTime)
{
    state->Stop(deltaTime);
}

void Character::move(double deltaTime, Direction direction)
{
    state->Move(deltaTime, direction);
}

#include <iostream>
using namespace std;
void Character::setState(BaseState *state)
{
    deallocate();
    this->state = state;
    cout << "Character::setState() " << state->to_string() << endl;
}

void Character::allocate()
{
    state = new GroundedState(this);
}

void Character::deallocate()
{
    delete state;
}
