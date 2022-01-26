#include "./circle.hpp"

#include <cmath>

using ::graphics::color::RGBA;
using ::graphics::shapes::Circle;
using ::math::Matrix;
using ::math::Vector;

#pragma region Constructor and Destructor
Circle::Circle()
{
    color_ = RGBA();
    BuildPoints(Vector::Zero(2), 0);
}

Circle::Circle(const Vector &origin, double radius)
{
    color_ = RGBA();
    radius_ = radius;
    BuildPoints(origin, radius);
}

Circle::Circle(const Vector &origin, double radius, const RGBA &color)
{
    color_ = color;
    radius_ = radius;
    BuildPoints(origin, radius);
}

Circle::Circle(const Circle &other)
{
    points_ = other.points_;
    radius_ = other.radius_;
    color_ = other.color_;
}

Circle::Circle(const Circle &&other)
{
    points_ = other.points_;
    radius_ = other.radius_;
    color_ = other.color_;
}
#pragma endregion // Constructor and Destructor

#pragma region Operator Overloads
Circle &Circle::operator=(const Circle &other)
{
    points_ = other.points_;
    color_ = other.color_;
    radius_ = other.radius_;
    return *this;
}

Circle &Circle::operator=(const Circle &&other)
{
    points_ = other.points_;
    color_ = other.color_;
    radius_ = other.radius_;
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