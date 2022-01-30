#include "./circle.hpp"

#include <cmath>

using ::graphics::color::RGBA;
using ::graphics::shapes::Circle;
using ::math::Matrix;
using ::math::Vector;

#pragma region Constructor and Destructor
Circle::Circle()
    : Model2D()
{
    color_ = RGBA();
    center_position_ = Vector::Zero(2);
    radius_ = 0;
    angle_ = 0;
    BuildPoints(Vector::Zero(2), 0);
}

Circle::Circle(const Vector &origin, double radius)
    : Model2D()
{
    color_ = RGBA();
    radius_ = radius;
    center_position_ = origin;
    BuildPoints(origin, radius);
}

Circle::Circle(const Vector &origin, double radius, const RGBA &color)
    : Model2D()
{
    color_ = color;
    radius_ = radius;
    center_position_ = origin;
    BuildPoints(origin, radius);
}

Circle::Circle(const Circle &other)
    : Model2D(other)
{
    points_ = other.points_;
    radius_ = other.radius_;
    color_ = other.color_;
    center_position_ = other.center_position_;
}

Circle::Circle(const Circle &&other)
    : Model2D(other)
{
    points_ = other.points_;
    radius_ = other.radius_;
    color_ = other.color_;
    center_position_ = other.center_position_;
}
#pragma endregion // Constructor and Destructor

#pragma region Operator Overloads
Circle &Circle::operator=(const Circle &other)
{
    points_ = other.points_;
    color_ = other.color_;
    radius_ = other.radius_;
    center_position_ = other.center_position_;
    return *this;
}

Circle &Circle::operator=(const Circle &&other)
{
    points_ = other.points_;
    color_ = other.color_;
    radius_ = other.radius_;
    center_position_ = other.center_position_;
    return *this;
}
#pragma endregion // Operator Overloads

#pragma region Private Methods
void Circle::BuildPoints(const Vector &origin, double radius)
{
    points_ = Matrix::Zero(segments_ + 1, 2);
    double angle = 0;
    for (int i = 0; i < segments_; i++)
    {
        points_[i][0] = origin[0] + radius * std::cos(angle);
        points_[i][1] = origin[1] + radius * std::sin(angle);
        angle += 2 * M_PI / segments_;
    }
    points_[segments_][0] = points_[0][0];
    points_[segments_][1] = points_[0][1];
}
#pragma endregion // Private Methods

double Circle::get_radius() const
{
    return radius_;
}