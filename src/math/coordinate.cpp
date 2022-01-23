#include "coordinate.hpp"
#include <stdexcept>

using namespace math;

#pragma region Constructor and Destructor
Coordinate::Coordinate(double x, double y)
{
    setX(x);
    setY(y);
}

Coordinate::Coordinate(const Coordinate &other)
{
    copy(other);
}
#pragma endregion // Constructor and Destructor

#pragma region Getter and Setter
double Coordinate::getX() const
{
    return x;
}

double Coordinate::getY() const
{
    return y;
}

void Coordinate::setX(double x)
{
    this->x = x;
}

void Coordinate::setY(double y)
{
    this->y = y;
}
#pragma endregion // Getter and Setter

#pragma region Operator Overloading
Coordinate &Coordinate::operator=(const Coordinate &other)
{
    copy(other);
    return *this;
}

bool Coordinate::operator==(const Coordinate &other) const
{
    return (x == other.getX() && y == other.getY());
}

bool Coordinate::operator!=(const Coordinate &other) const
{
    return !(*this == other);
}

double Coordinate::operator[](int i) const
{
    if (i == 0)
        return x;
    else if (i == 1)
        return y;
    else
        throw std::out_of_range("Index out of range");
}

double &Coordinate::operator[](int i)
{
    if (i == 0)
        return x;
    else if (i == 1)
        return y;
    else
        throw std::out_of_range("Index out of range");
}
#pragma endregion // Operator Overloading

#pragma region Static Function
Coordinate Coordinate::zero()
{
    return Coordinate(0, 0);
}
#pragma endregion // Static Function

#pragma region Private Function
void Coordinate::copy(const Coordinate &other)
{
    x = other.getX();
    y = other.getY();
}
#pragma endregion // Private Function
