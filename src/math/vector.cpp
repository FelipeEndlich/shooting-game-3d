#include "vector.hpp"
#include <stdexcept>
#include <string>
#include <cmath>

using math::Vector;

#pragma region Constructor and Destructor
Vector::Vector()
{
    Allocate(0);
}

Vector::Vector(int dimension)
{
    Allocate(dimension);
}

Vector::Vector(const Vector &other)
{
    Copy(other);
}

Vector::~Vector()
{
    Deallocate();
}
#pragma endregion // Constructor and Destructor

#pragma region Operator Overloading
Vector &Vector::operator=(const Vector &other)
{
    if (this != &other)
    {
        Deallocate();
        Copy(other);
    }
    return *this;
}

bool Vector::operator==(const Vector &other) const
{
    if (this->dimension_ != other.dimension_)
        return false;

    for (int i = 0; i < this->dimension_; i++)
        if (this->values_[i] != other.values_[i])
            return false;

    return true;
}

bool Vector::operator!=(const Vector &other) const
{
    return !(*this == other);
}

Vector Vector::operator+(const Vector &other) const
{
    if (this->dimension_ != other.dimension_)
        throw std::invalid_argument("Dimension mismatch");

    Vector result(this->dimension_);

    for (int i = 0; i < this->dimension_; i++)
        result.values_[i] = this->values_[i] + other.values_[i];

    return result;
}

Vector Vector::operator-(const Vector &other) const
{
    if (this->dimension_ != other.dimension_)
        throw std::invalid_argument("Dimension mismatch");

    Vector result(this->dimension_);

    for (int i = 0; i < this->dimension_; i++)
        result.values_[i] = this->values_[i] - other.values_[i];

    return result;
}

Vector Vector::operator*(const double &other) const
{
    Vector result(this->dimension_);

    for (int i = 0; i < this->dimension_; i++)
        result.values_[i] = this->values_[i] * other;

    return result;
}

Vector Vector::operator/(const double &other) const
{
    Vector result(this->dimension_);

    for (int i = 0; i < this->dimension_; i++)
        result.values_[i] = this->values_[i] / other;

    return result;
}

Vector Vector::operator^(const int &other) const
{
    if (other < 0)
        throw std::invalid_argument("Power must be greater than 0");

    Vector result(this->dimension_);

    for (int i = 0; i < this->dimension_; i++)
        result.values_[i] = pow(this->values_[i], other);

    return result;
}

Vector &Vector::operator+=(const Vector &other)
{
    if (this->dimension_ != other.dimension_)
        throw std::invalid_argument("Dimension mismatch");

    for (int i = 0; i < this->dimension_; i++)
        this->values_[i] += other.values_[i];

    return *this;
}

Vector &Vector::operator-=(const Vector &other)
{
    if (this->dimension_ != other.dimension_)
        throw std::invalid_argument("Dimension mismatch");

    for (int i = 0; i < this->dimension_; i++)
        this->values_[i] -= other.values_[i];

    return *this;
}

Vector &Vector::operator*=(const double &other)
{
    for (int i = 0; i < this->dimension_; i++)
        this->values_[i] *= other;

    return *this;
}

Vector &Vector::operator/=(const double &other)
{
    for (int i = 0; i < this->dimension_; i++)
        this->values_[i] /= other;

    return *this;
}

Vector &Vector::operator^=(const int &other)
{
    if (other < 0)
        throw std::invalid_argument("Power must be greater than 0");

    for (int i = 0; i < this->dimension_; i++)
        this->values_[i] = pow(this->values_[i], other);

    return *this;
}

double Vector::operator[](int i) const
{
    return this->values_[i];
}

double &Vector::operator[](int i)
{
    return this->values_[i];
}
#pragma endregion // Operator Overloading

#pragma region Getters and Setters
int Vector::get_dimension() const
{
    return this->dimension_;
}

void Vector::set_dimension(int dimension)
{
    if (dimension < 0)
        throw std::invalid_argument("Dimension must be greater than 0");

    Deallocate();
    Allocate(dimension);
}
#pragma endregion // Getters and Setters

#pragma region Static Methods
Vector Vector::Zero(int dimension)
{
    return Vector::Fill(dimension, 0.0);
}

Vector Vector::Fill(int dimension, double value)
{
    Vector result(dimension);
    for (int i = 0; i < dimension; i++)
        result.values_[i] = value;

    return result;
}

Vector Vector::ThreeDimPoint(double x, double y, double z)
{
    Vector point(3);
    point.values_[0] = x;
    point.values_[1] = y;
    point.values_[2] = z;
    
    return point;
}
#pragma endregion // Static Methods

#pragma region Other Methods
double Vector::DotProduct(const Vector &other) const
{
    if (this->dimension_ != other.dimension_)
        throw std::invalid_argument("Dimension mismatch");

    double result = 0.0;
    for (int i = 0; i < this->dimension_; i++)
        result += this->values_[i] * other.values_[i];

    return result;
}

Vector Vector::CrossProduct(const Vector &other) const
{
    if (this->dimension_ != 3 || other.dimension_ != 3)
        throw std::invalid_argument("Dimension mismatch");

    Vector result(3);
    result.values_[0] = this->values_[1] * other.values_[2] - this->values_[2] * other.values_[1];
    result.values_[1] = this->values_[2] * other.values_[0] - this->values_[0] * other.values_[2];
    result.values_[2] = this->values_[0] * other.values_[1] - this->values_[1] * other.values_[0];

    return result;
}

double Vector::Magnitude() const
{
    double result = 0.0;
    for (int i = 0; i < this->dimension_; i++)
        result += this->values_[i] * this->values_[i];

    return sqrt(result);
}

Vector Vector::Normalize() const
{
    return *this / Magnitude();
}

double Vector::Distance(const Vector &other) const
{
    return (*this - other).Magnitude();
}

double Vector::Angle(const Vector &other) const
{
    return acos(DotProduct(other) / (Magnitude() * other.Magnitude()));
}

void Vector::Swap(Vector &other)
{
    std::swap(this->dimension_, other.dimension_);
    std::swap(this->values_, other.values_);
}

void Vector::Resize(int dimension)
{
    if (dimension == this->dimension_)
        return;

    Deallocate();
    Allocate(dimension);
}

std::string Vector::to_string() const
{
    std::string result = "";
    for (int i = 0; i < this->dimension_; i++)
        result += std::to_string(this->values_[i]) + " ";

    return result;
}

#pragma endregion // Other Methods

#pragma region Protected Methods
void Vector::Copy(const Vector &other)
{
    Allocate(other.dimension_);
    for (int i = 0; i < dimension_; i++)
        values_[i] = other.values_[i];
}

void Vector::Allocate(int dimension)
{
    this->dimension_ = dimension;
    values_.resize(dimension);
}

void Vector::Deallocate()
{
    values_.clear();
    dimension_ = 0;
}
#pragma endregion // Protected Methods