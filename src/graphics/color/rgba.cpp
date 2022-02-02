#include "rgba.hpp"

using namespace graphics::color;

#pragma region Constructors and Destructors
RGBA::RGBA()
{
    red_ = 0;
    green_ = 0;
    blue_ = 0;
    alpha_ = 255;
}

RGBA::RGBA(unsigned int red, unsigned int green, unsigned int blue)
{
    red_ = red;
    green_ = green;
    blue_ = blue;
    alpha_ = 255;
}

RGBA::RGBA(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha)
{
    red_ = red;
    green_ = green;
    blue_ = blue;
    alpha_ = alpha;
}

RGBA::RGBA(const RGBA &other)
{
    red_ = other.red_;
    green_ = other.green_;
    blue_ = other.blue_;
    alpha_ = other.alpha_;
}

RGBA::RGBA(const RGBA &&other)
{
    red_ = other.red_;
    green_ = other.green_;
    blue_ = other.blue_;
    alpha_ = other.alpha_;
}

#pragma endregion // Constructors and Destructors

#pragma region Operators
RGBA &RGBA::operator=(const RGBA &other)
{
    red_ = other.red_;
    green_ = other.green_;
    blue_ = other.blue_;
    alpha_ = other.alpha_;

    return *this;
}

RGBA &RGBA::operator=(const RGBA &&other)
{
    red_ = other.red_;
    green_ = other.green_;
    blue_ = other.blue_;
    alpha_ = other.alpha_;

    return *this;
}
#pragma endregion // Operators

#pragma region Getters and Setters
unsigned int RGBA::get_red() const
{
    return this->red_;
}

unsigned int RGBA::get_green() const
{
    return this->green_;
}
unsigned int RGBA::get_blue() const
{
    return this->blue_;
}

unsigned int RGBA::get_alpha() const
{
    return this->alpha_;
}

void RGBA::set_red(unsigned int red)
{
    this->red_ = red;
}

void RGBA::set_green(unsigned int green)
{
    this->green_ = green;
}

void RGBA::set_blue(unsigned int blue)
{
    this->blue_ = blue;
}

void RGBA::set_alpha(unsigned int alpha)
{
    this->alpha_ = alpha;
}
#pragma endregion // Getters and Setters