#include "character.hpp"

using namespace graphics::elements::character;

Character::Character()
    : RigidBody(2)
{
}

Character::Character(Vector &initialPosition, double radius, RGBA &color)
    : RigidBody(2)
{
    position = initialPosition;
    shape = Circle(position, radius, color);
}

void Character::render()
{
    shape.draw();
}