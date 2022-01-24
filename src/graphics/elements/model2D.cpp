#include "model2D.hpp"
#include <cmath>
#include <stdexcept>
using namespace graphics::elements;

#pragma region Constructors and Destructors
Model2D::Model2D()
    : Model()
{
}

Model2D::Model2D(const math::Matrix &matrix)
    : Model(matrix)
{
    validateMatrix(points);
}

Model2D::Model2D(const math::Matrix &matrix, const graphics::color::RGBA &color)
    : Model(matrix, color)
{
    validateMatrix(points);
}

Model2D::Model2D(const Model2D &other)
    : Model(other)
{
    validateMatrix(points);
}

Model2D::Model2D(const Model2D &&other)
    : Model(other)
{
    validateMatrix(points);
}
#pragma endregion // Constructors and Destructors

#pragma region Methods
void Model2D::translate(const math::Vector &vector)
{
    for (int i = 0; i < points.getRows(); i++)
        points[i] += vector;
}

void Model2D::scale(const math::Vector center, const math::Vector &vector)
{
    math::Matrix T = math::Matrix::identity(3, 3);
    T[0][2] = center[0];
    T[1][2] = center[1];

    math::Matrix S = math::Matrix::identity(3, 3);
    S[0][0] = vector[0];
    S[1][1] = vector[1];

    math::Matrix T_rev = T;
    T_rev[0][2] *= -1;
    T_rev[1][2] *= -1;

    transform(T * S * T_rev);
}

void Model2D::rotate(const math::Vector center, double radians)
{
    math::Matrix T = math::Matrix::identity(3, 3);
    T[0][2] = center[0];
    T[1][2] = center[1];

    math::Matrix R = math::Matrix::identity(3, 3);
    R[0][0] = cos(radians);
    R[0][1] = -sin(radians);
    R[1][0] = sin(radians);
    R[1][1] = cos(radians);

    math::Matrix T_rev = T;
    T_rev[0][2] *= -1;
    T_rev[1][2] *= -1;

    transform(T * R * T_rev);
}

void Model2D::transform(const math::Matrix &matrix)
{
    for (int i = 0; i < points.getRows(); i++)
        points[i] = matrix * points[i];
}

void Model2D::transform(const math::Vector center, const math::Vector &translate, const math::Vector &scale, double radians)
{
    math::Matrix T = math::Matrix::identity(3, 3);
    T[0][2] = center[0];
    T[1][2] = center[1];

    math::Matrix S = math::Matrix::identity(3, 3);
    S[0][0] = scale[0];
    S[1][1] = scale[1];

    math::Matrix R = math::Matrix::identity(3, 3);
    R[0][0] = cos(radians);
    R[0][1] = -sin(radians);
    R[1][0] = sin(radians);
    R[1][1] = cos(radians);

    math::Matrix T_rev = T;
    T_rev[0][2] *= -1;
    T_rev[1][2] *= -1;

    transform(T * R * S * T_rev);
}
#pragma endregion // Methods

#pragma region Private Methods
void Model2D::validateMatrix(const math::Matrix &matrix)
{
    if (matrix.getColumns() != 2)
    {
        throw std::invalid_argument("The matrix must have 2 columns.");
    }
}
#pragma endregion // Private Methods