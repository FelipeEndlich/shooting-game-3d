#include "./circle.hpp"
#include <cmath>
using namespace graphics::shapes;

#pragma region Constructor and Destructor
Circle::Circle()
{
    this->color = graphics::color::RGBA();
    buildPoints(math::Vector::zero(2), 0);
}

Circle::Circle(const math::Vector &origin, double radius)
{
    this->color = graphics::color::RGBA();
    buildPoints(origin, radius);
}

Circle::Circle(const math::Vector &origin, double radius, const graphics::color::RGBA &color)
{
    this->color = color;
    buildPoints(origin, radius);
}

Circle::Circle(const Circle &other)
{
    this->points = other.points;
    this->color = other.color;
}

Circle::Circle(const Circle &&other)
{
    this->points = other.points;
    this->color = other.color;
}

Circle::~Circle()
{
}
#pragma endregion // Constructor and Destructor

#pragma region Operator Overloads
Circle &Circle::operator=(const Circle &other)
{
    this->points = other.points;
    this->color = other.color;
    return *this;
}

Circle &Circle::operator=(const Circle &&other)
{
    this->points = other.points;
    this->color = other.color;
    return *this;
}
#pragma endregion // Operator Overloads

#pragma region Private Methods
void Circle::buildPoints(const math::Vector &origin, double radius)
{
    points = math::Matrix::zero(segments + 1, 2);
    double angle = 0;
    for (int i = 0; i < segments; i++)
    {
        points[i][0] = origin[0] + radius * std::cos(angle);
        points[i][1] = origin[1] + radius * std::sin(angle);
        angle += 2 * M_PI / segments;
    }
    points[segments][0] = points[0][0];
    points[segments][1] = points[0][1];
}
#pragma endregion // Private Methods