#include "rectangle.hpp"

using ::graphics::color::RGBA;
using ::graphics::shapes::Rectangle;
using ::math::Matrix;
using ::math::Vector;

#pragma region Constructor and Destructor
Rectangle::Rectangle()
    : Model2D()
{
    color_ = RGBA();
    angle_ = 0;
    BuildPoints(Vector::Zero(2), 0, 0);
}

Rectangle::Rectangle(const Vector &origin, double width, double height)
    : Model2D()
{
    color_ = RGBA();
    width_ = width;
    height_ = height;

    angle_ = 0;

    BuildPoints(origin, width, height);
}

Rectangle::Rectangle(const Vector &origin, double width, double height, const RGBA &color)
    : Model2D()
{
    color_ = color;
    width_ = width;
    height_ = height;
    angle_ = 0;
    BuildPoints(origin, width, height);
}

Rectangle::Rectangle(const Rectangle &other)
    : Model2D(other)
{
    *this = other;
}

Rectangle::Rectangle(const Rectangle &&other)
    : Model2D(other)
{
    *this = other;
}
#pragma endregion // Constructor and Destructor

#pragma region Operator Overloads
Rectangle &Rectangle::operator=(const Rectangle &other)
{
    points_ = other.points_;
    color_ = other.color_;
    width_ = other.width_;
    height_ = other.height_;
    angle_ = other.angle_;
    return *this;
}

Rectangle &Rectangle::operator=(const Rectangle &&other)
{
    points_ = other.points_;
    color_ = other.color_;
    width_ = other.width_;
    height_ = other.height_;
    angle_ = other.angle_;
    return *this;
}
#pragma endregion // Operator Overloads

#pragma region Private Methods
void Rectangle::BuildPoints(const Vector &origin, double width, double height)
{
    points_ = Matrix::Zero(4, 2);
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

Vector Rectangle::get_center_position() const
{
    return Vector(points_[0] + points_[1] + points_[2] + points_[3]) / 4;
}