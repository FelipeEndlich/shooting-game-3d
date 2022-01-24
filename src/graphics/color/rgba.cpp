#include "rgba.hpp"

using namespace graphics::color;

#pragma region Constructors and Destructors
RGBA::RGBA()
{
    this->r = 0;
    this->g = 0;
    this->b = 0;
    this->a = 255;
}

RGBA::RGBA(unsigned int r, unsigned int g, unsigned int b)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = 255;
}

RGBA::RGBA(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

RGBA::RGBA(const RGBA &other)
{
    this->r = other.r;
    this->g = other.g;
    this->b = other.b;
    this->a = other.a;
}

RGBA::RGBA(const RGBA &&other)
{
    this->r = other.r;
    this->g = other.g;
    this->b = other.b;
    this->a = other.a;
}

#pragma endregion // Constructors and Destructors

#pragma region Operators
RGBA &RGBA::operator=(const RGBA &other)
{
    this->r = other.r;
    this->g = other.g;
    this->b = other.b;
    this->a = other.a;

    return *this;
}

RGBA &RGBA::operator=(const RGBA &&other)
{
    this->r = other.r;
    this->g = other.g;
    this->b = other.b;
    this->a = other.a;

    return *this;
}
#pragma endregion // Operators

#pragma region Getters and Setters
unsigned int RGBA::getR() const
{
    return this->r;
}

unsigned int RGBA::getG() const
{
    return this->g;
}
unsigned int RGBA::getB() const
{
    return this->b;
}

unsigned int RGBA::getA() const
{
    return this->a;
}

void RGBA::setR(unsigned int r)
{
    this->r = r;
}

void RGBA::setG(unsigned int g)
{
    this->g = g;
}

void RGBA::setB(unsigned int b)
{
    this->b = b;
}

void RGBA::setA(unsigned int a)
{
    this->a = a;
}
#pragma endregion // Getters and Setters