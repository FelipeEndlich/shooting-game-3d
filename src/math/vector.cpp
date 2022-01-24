#include "vector.hpp"
#include <stdexcept>
#include <string>
#include <cmath>

using namespace math;

#pragma region Constructor and Destructor
Vector::Vector()
{
    allocate(0);
}

Vector::Vector(int dimension)
{
    allocate(dimension);
}

Vector::Vector(const Vector &other)
{
    copy(other);
}

Vector::~Vector()
{
    deallocate();
}
#pragma endregion // Constructor and Destructor

#pragma region Operator Overloading
Vector &Vector::operator=(const Vector &other)
{
    if (this != &other)
    {
        deallocate();
        copy(other);
    }
    return *this;
}

bool Vector::operator==(const Vector &other) const
{
    if (this->dimension != other.dimension)
        return false;

    for (int i = 0; i < this->dimension; i++)
        if (this->values[i] != other.values[i])
            return false;

    return true;
}

bool Vector::operator!=(const Vector &other) const
{
    return !(*this == other);
}

Vector Vector::operator+(const Vector &other) const
{
    if (this->dimension != other.dimension)
        throw std::invalid_argument("Dimension mismatch");

    Vector result(this->dimension);

    for (int i = 0; i < this->dimension; i++)
        result.values[i] = this->values[i] + other.values[i];

    return result;
}

Vector Vector::operator-(const Vector &other) const
{
    if (this->dimension != other.dimension)
        throw std::invalid_argument("Dimension mismatch");

    Vector result(this->dimension);

    for (int i = 0; i < this->dimension; i++)
        result.values[i] = this->values[i] - other.values[i];

    return result;
}

Vector Vector::operator*(const double &other) const
{
    Vector result(this->dimension);

    for (int i = 0; i < this->dimension; i++)
        result.values[i] = this->values[i] * other;

    return result;
}

Vector Vector::operator/(const double &other) const
{
    Vector result(this->dimension);

    for (int i = 0; i < this->dimension; i++)
        result.values[i] = this->values[i] / other;

    return result;
}

Vector Vector::operator^(const int &other) const
{
    if (other < 0)
        throw std::invalid_argument("Power must be greater than 0");

    Vector result(this->dimension);

    for (int i = 0; i < this->dimension; i++)
        result.values[i] = pow(this->values[i], other);

    return result;
}

Vector &Vector::operator+=(const Vector &other)
{
    if (this->dimension != other.dimension)
        throw std::invalid_argument("Dimension mismatch");

    for (int i = 0; i < this->dimension; i++)
        this->values[i] += other.values[i];

    return *this;
}

Vector &Vector::operator-=(const Vector &other)
{
    if (this->dimension != other.dimension)
        throw std::invalid_argument("Dimension mismatch");

    for (int i = 0; i < this->dimension; i++)
        this->values[i] -= other.values[i];

    return *this;
}

Vector &Vector::operator*=(const double &other)
{
    for (int i = 0; i < this->dimension; i++)
        this->values[i] *= other;

    return *this;
}

Vector &Vector::operator/=(const double &other)
{
    for (int i = 0; i < this->dimension; i++)
        this->values[i] /= other;

    return *this;
}

Vector &Vector::operator^=(const int &other)
{
    if (other < 0)
        throw std::invalid_argument("Power must be greater than 0");

    for (int i = 0; i < this->dimension; i++)
        this->values[i] = pow(this->values[i], other);

    return *this;
}

double Vector::operator[](int i) const
{
    return this->values[i];
}

double &Vector::operator[](int i)
{
    return this->values[i];
}
#pragma endregion // Operator Overloading

#pragma region Static Methods
Vector Vector::zero(int dimension)
{
    return Vector::fill(dimension, 0.0);
}

Vector Vector::fill(int dimension, double value)
{
    Vector result(dimension);
    for (int i = 0; i < dimension; i++)
        result.values[i] = value;

    return result;
}
#pragma endregion // Static Methods

#pragma region Other Methods
double Vector::dotProduct(const Vector &other) const
{
    if (this->dimension != other.dimension)
        throw std::invalid_argument("Dimension mismatch");

    double result = 0.0;
    for (int i = 0; i < this->dimension; i++)
        result += this->values[i] * other.values[i];

    return result;
}

Vector Vector::crossProduct(const Vector &other) const
{
    if (this->dimension != 3 || other.dimension != 3)
        throw std::invalid_argument("Dimension mismatch");

    Vector result(3);
    result.values[0] = this->values[1] * other.values[2] - this->values[2] * other.values[1];
    result.values[1] = this->values[2] * other.values[0] - this->values[0] * other.values[2];
    result.values[2] = this->values[0] * other.values[1] - this->values[1] * other.values[0];

    return result;
}

double Vector::magnitude() const
{
    double result = 0.0;
    for (int i = 0; i < this->dimension; i++)
        result += this->values[i] * this->values[i];

    return sqrt(result);
}

Vector Vector::normalize() const
{
    return *this / magnitude();
}

double Vector::distance(const Vector &other) const
{
    return (*this - other).magnitude();
}

double Vector::angle(const Vector &other) const
{
    return acos(dotProduct(other) / (magnitude() * other.magnitude()));
}

void Vector::swap(Vector &other)
{
    std::swap(this->dimension, other.dimension);
    std::swap(this->values, other.values);
}

void Vector::resize(int dimension)
{
    if (dimension == this->dimension)
        return;

    deallocate();
    allocate(dimension);
}

std::string Vector::to_string() const
{
    std::string result = "";
    for (int i = 0; i < this->dimension; i++)
        result += std::to_string(this->values[i]) + " ";

    return result;
}

#pragma endregion // Other Methods

#pragma region Protected Methods
void Vector::copy(const Vector &other)
{
    allocate(other.dimension);
    for (int i = 0; i < dimension; i++)
        values[i] = other.values[i];
}

void Vector::allocate(int dimension)
{
    this->dimension = dimension;
    values.resize(dimension);
}

void Vector::deallocate()
{
    values.clear();
    dimension = 0;
}
#pragma endregion // Protected Methods