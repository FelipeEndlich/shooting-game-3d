#include "rectangle.hpp"

using ::graphics::shapes::Rectangle;
using ::graphics::color::RGBA;
using ::math::Vector;
using ::math::Matrix;

#pragma region Constructor and Destructor
Rectangle::Rectangle()
{
    color_ = RGBA();
    BuildPoints(Vector::zero(2), 0, 0);
}

Rectangle::Rectangle(const Vector &origin, double width, double height)
{
    color_ = RGBA();
    BuildPoints(origin, width, height);
}

Rectangle::Rectangle(const Vector &origin, double width, double height, const RGBA &color)
{
    color_ = color;
    BuildPoints(origin, width, height);
}

Rectangle::Rectangle(const Rectangle &other)
{
    points_ = other.points_;
    color_ = other.color_;
}

Rectangle::Rectangle(const Rectangle &&other)
{
    points_ = other.points_;
    color_ = other.color_;
}
#pragma endregion // Constructor and Destructor

#pragma region Operator Overloads
Rectangle &Rectangle::operator=(const Rectangle &other)
{
    points_ = other.points_;
    color_ = other.color_;
    return *this;
}

Rectangle &Rectangle::operator=(const Rectangle &&other)
{
    points_ = other.points_;
    color_ = other.color_;
    return *this;
}
#pragma endregion // Operator Overloads

#pragma region Private Methods
void Rectangle::BuildPoints(const Vector &origin, double width, double height)
{
    points_ = Matrix::zero(4, 2);
    this->width_ = width;
    this->height_ = height;

    points_[0][0] = origin[0];
    points_[0][1] = origin[1];

    points_[1][0] = origin[0] + width;
    points_[1][1] = origin[1];

    points_[2][0] = origin[0] + width;
    points_[2][1] = origin[1] + height;

    points_[3][0] = origin[0];
    points_[3][1] = origin[1] + height;
}
#pragma endregion // Private Methods

#pragma region Getters and Setters
double Rectangle::get_width() const
{
    return width_;
}

double Rectangle::get_height() const
{
    return height_;
}
#pragma endregion // Getters and Setters