#include "rectangle.hpp"

using namespace graphics::elements;

#pragma region Constructor and Destructor
Rectangle::Rectangle()
{
    this->points = math::Matrix::zero(4, 2);
    buildPoints(math::Vector::zero(2), 0, 0);
}

Rectangle::Rectangle(const math::Vector &origin, double width, double height)
{
    this->color = graphics::color::RGBA();
    buildPoints(origin, width, height);
}

Rectangle::Rectangle(const math::Vector &origin, double width, double height, const graphics::color::RGBA &color)
{
    this->color = color;
    buildPoints(origin, width, height);
}

Rectangle::Rectangle(const Rectangle &other)
{
    this->points = other.points;
    this->color = other.color;
}

Rectangle::Rectangle(const Rectangle &&other)
{
    this->points = other.points;
    this->color = other.color;
}

Rectangle::~Rectangle()
{
}
#pragma endregion // Constructor and Destructor

#pragma region Operator Overloads
Rectangle &Rectangle::operator=(const Rectangle &other)
{
    this->points = other.points;
    this->color = other.color;
    return *this;
}

Rectangle &Rectangle::operator=(const Rectangle &&other)
{
    this->points = other.points;
    this->color = other.color;
    return *this;
}
#pragma endregion // Operator Overloads

#pragma region Private Methods
void Rectangle::buildPoints(const math::Vector &origin, double width, double height)
{
    points = math::Matrix::zero(4, 2);
    this->width = width;
    this->height = height;

    points[0][0] = origin[0];
    points[0][1] = origin[1];

    points[1][0] = origin[0] + width;
    points[1][1] = origin[1];

    points[2][0] = origin[0] + width;
    points[2][1] = origin[1] + height;

    points[3][0] = origin[0];
    points[3][1] = origin[1] + height;
}
#pragma endregion // Private Methods