#include "model_2d.hpp"

#include <stdexcept>
#include <cmath>

#include <GL/glut.h>

using ::graphics::color::RGBA;
using ::graphics::shapes::Model2D;
using ::math::Matrix;
using ::math::Vector;

#pragma region Constructors and Destructors
Model2D::Model2D()
    : Model()
{
}

Model2D::Model2D(const Matrix &matrix)
    : Model(matrix)
{
    ValidateMatrix(points_);
}

Model2D::Model2D(const Matrix &matrix, const RGBA &color)
    : Model(matrix, color)
{
    ValidateMatrix(points_);
}

Model2D::Model2D(const Model2D &other)
    : Model(other)
{
    ValidateMatrix(points_);
}

Model2D::Model2D(const Model2D &&other)
    : Model(other)
{
    ValidateMatrix(points_);
}
#pragma endregion // Constructors and Destructors

#pragma region Methods
void Model2D::Translate(const Vector &vector)
{
    for (int i = 0; i < points_.get_rows(); i++)
        points_[i] += vector;
}

void Model2D::Scale(const Vector &center, const Vector &vector)
{
    Transform(center, vector, 0);
}

#include <iostream>
using namespace std;
void Model2D::Rotate(const Vector &center, double radians)
{
    Transform(center, Vector::Zero(2), radians);
}

void Model2D::Transform(const Matrix &matrix)
{
    for (int i = 0; i < points_.get_rows(); i++)
    {
        Vector point = Vector::Fill(3, 1);
        point[0] = points_[i][0];
        point[1] = points_[i][1];

        point = matrix * point;

        points_[i][0] = point[0];
        points_[i][1] = point[1];
    }
}

void Model2D::Transform(const Vector &center, const Vector &scale, double radians)
{
    Matrix translate_matrix = Matrix::Identity(3, 3);
    translate_matrix[0][2] = -center[0];
    translate_matrix[1][2] = -center[1];

    Matrix scale_matrix = Matrix::Identity(3, 3);
    scale_matrix[0][0] = scale[0];
    scale_matrix[1][1] = scale[1];

    Matrix rotate_matrix = Matrix::Identity(3, 3);
    rotate_matrix[0][0] = cos(radians);
    rotate_matrix[0][1] = -sin(radians);
    rotate_matrix[1][0] = sin(radians);
    rotate_matrix[1][1] = cos(radians);

    Matrix translate_back_matrix = Matrix::Identity(3, 3);
    translate_back_matrix[0][2] = center[0];
    translate_back_matrix[1][2] = center[1];

    Transform(translate_back_matrix * rotate_matrix * translate_matrix);
}

void Model2D::Draw()
{
    double red = color_.get_red() / 255.0;
    double green = color_.get_green() / 255.0;
    double blue = color_.get_blue() / 255.0;
    double alpha = color_.get_alpha() / 255.0;

    glColor4d(red, green, blue, alpha);
    glBegin(GL_POLYGON);
    for (int i = 0; i < points_.get_rows(); i++)
        glVertex2d(points_[i][0], points_[i][1]);

    glEnd();
}
#pragma endregion // Methods

#pragma region Private Methods
void Model2D::ValidateMatrix(const math::Matrix &matrix)
{
    if (matrix.get_columns() != 2)
    {
        throw std::invalid_argument("The matrix must have 2 columns.");
    }
}
#pragma endregion // Private Methods