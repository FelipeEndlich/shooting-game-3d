#include "./character.hpp"
#include "./state/groundedState.hpp"
#include "../../../physics/rigidBody.hpp"

using namespace math;
using namespace graphics::color;
using namespace graphics::shapes;
using namespace graphics::elements::character;

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
        this->state = other.state->clone();
    }
    return *this;
}

void Character::render()
{
    shape.draw();
}

void Character::fall(double deltaTime)
{
    state->fall(deltaTime);
}

void Character::jump(double deltaTime)
{
    state->jump(deltaTime);
}

void Character::stop(double deltaTime)
{
    state->stop(deltaTime);
}

void Character::move(double deltaTime, Direction direction)
{
    state->move(deltaTime, direction);
}

#include <iostream>
using namespace std;
void Character::setState(State *state)
{
    deallocate();
    this->state = state;
    cout << "Character::setState() " << state->toString() << endl;
}

void Character::allocate()
{
    state = new GroundedState(this);
}

void Character::deallocate()
{
    delete state;
}
