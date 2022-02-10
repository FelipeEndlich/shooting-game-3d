#include "model_3d.hpp"

#include <cmath>

#include <iostream>

#include <stdexcept>

#include <GL/glut.h>

#include "./model.hpp"
#include "./../color/rgba.hpp"
#include "./../../math/matrix.hpp"
#include "./../../math/vector.hpp"

using ::graphics::color::RGBA;
using ::graphics::shapes::Model;
using ::graphics::shapes::Model3D;
using ::math::Matrix;
using ::math::Vector;

Model3D::Model3D()
    : Model(), angle_(0)
{
}

Model3D::Model3D(const math::Matrix &matrix)
    : Model(matrix), angle_(0)
{
    ValidateMatrix(matrix);
}

Model3D::Model3D(const math::Matrix &matrix, const graphics::color::RGBA &color)
    : Model(matrix, color), angle_(0)
{
    ValidateMatrix(matrix);
}

Model3D::Model3D(const Model3D &other)
    : Model(other), angle_(other.angle_)
{
}

Model3D::Model3D(const Model3D &&other)
    : Model(other), angle_(other.angle_)
{
}

void Model3D::Translate(double dx, double dy, double dz)
{
    Vector translation(3);
    translation[0] = dx;
    translation[1] = dy;
    translation[2] = dz;
    Translate(translation);
}

void Model3D::Translate(const math::Vector &vector)
{
    for (int i = 0; i < points_.get_rows(); i++)
        points_[i] += vector;
}

void Model3D::Scale(double x, double y, double z, double sx, double sy, double sz)
{
    Transform(x, y, z, sx, sy, sz, 0, 0, 0);
}

void Model3D::Scale(const math::Vector &center, double sx, double sy, double sz)
{
    Transform(center, sx, sy, sz, 0, 0, 0);
}

void Model3D::Scale(double x, double y, double z, const math::Vector &scale_vector)
{
    Transform(x, y, z, scale_vector, 0, 0, 0);
}

void Model3D::Scale(const math::Vector &center, const math::Vector &scale_vector)
{
    Transform(center, scale_vector, 0, 0, 0);
}

void Model3D::Rotate(double x, double y, double z, double phi, double psi, double theta)
{
    Transform(x, y, z, 1, 1, 1, phi, psi, theta);
}

void Model3D::Rotate(double x, double y, double z, math::Vector &radians)
{
    Transform(x, y, z, 1, 1, 1, radians);
}

void Model3D::Rotate(const math::Vector &center, double phi, double psi, double theta)
{
    Transform(center, 1, 1, 1, phi, psi, theta);
}

void Model3D::Rotate(const math::Vector &center, const math::Vector &radians)
{
    Transform(center, 1, 1, 1, radians);
}

void Model3D::Transform(const math::Matrix &matrix)
{
    for (int i = 0; i < points_.get_rows(); i++)
    {
        Vector point = Vector::Fill(4, 1);
        point[0] = points_[i][0];
        point[1] = points_[i][1];
        point[2] = points_[i][2];

        point = matrix * point;

        points_[i][0] = point[0];
        points_[i][1] = point[1];
        points_[i][2] = point[2];
    }
}

void Model3D::Transform(double x, double y, double z, double sx, double sy, double sz, double phi, double psi, double theta)
{
    // Phi, Psi and Theta must be in radians
    //Vector point;

    // Centering the model
    for (int i = 0; i < points_.get_rows(); i++) {
        points_[i][0] -= x;
        points_[i][1] -= y;
        points_[i][2] -= z;
    }

    // Rotating the model
    Matrix r_x, r_y, r_z, r_m;

    r_x = Matrix::FourDimMatrix(
        1,        0,         0, 0,
        0, cos(phi), -sin(phi), 0,
        0, sin(phi),  cos(phi), 0,
        0,        0,         0, 1
    );
    r_y = Matrix::FourDimMatrix(
         cos(psi),        0,         sin(psi), 0,
                0,        1,                0, 0,
        -sin(psi),        0,         cos(psi), 0,
        0,                0,                0, 1
    );
    r_z = Matrix::FourDimMatrix(
         cos(theta), -sin(theta), 0, 0,
         sin(theta),  cos(theta), 0, 0,
                  0,           0, 1, 0,
                  0,           0, 0, 1
    );

    r_m = r_y.Inverse() * r_z.Inverse() * r_x * r_z * r_y;

    // Translating the model
    Matrix t_m;
    t_m = Matrix::FourDimMatrix(
        1, 0, 0, sx + x,
        0, 1, 0, sy + y,
        0, 0, 1, sy + z,
        0, 0, 0, 1
    );

    Matrix tf_m;
    tf_m = t_m * r_m;

    for (int i = 0; i < points_.get_rows(); i++) {
        Vector point = points_[i];
        Vector point_plus(4);

        point_plus[0] = point[0]; point_plus[1] = point[1];
        point_plus[2] = point[2]; point_plus[3] = 1;
        point_plus = tf_m * point_plus;
        
        points_[i][0] = point_plus[0];
        points_[i][1] = point_plus[1];
        points_[i][2] = point_plus[2];
    }
}

void Model3D::Transform(const math::Vector &center, double sx, double sy, double sz, double phi, double psi, double theta)
{
    Transform(center[0], center[1], center[2], sx, sy, sz, phi, psi, theta);
}

void Model3D::Transform(double x, double y, double z, const math::Vector &scale, double phi, double psi, double theta)
{
    Transform(x, y, z, scale[0], scale[1], scale[2], phi, psi, theta);
}

void Model3D::Transform(double x, double y, double z, double sx, double sy, double sz, const math::Vector &radians)
{
    Transform(x, y, z, sx, sy, sz, radians[0], radians[1], radians[2]);
}

void Model3D::Transform(const math::Vector &center, const math::Vector &scale, double phi, double psi, double theta)
{
    Transform(center[0], center[1], center[2], scale[0], scale[1], scale[2], phi, psi, theta);
}

void Model3D::Transform(const math::Vector &center, double sx, double sy, double sz, const math::Vector &radians)
{
    Transform(center[0], center[1], center[2], sx, sy, sz, radians[0], radians[1], radians[2]);
}

void Model3D::Transform(double x, double y, double z, const math::Vector &scale, const math::Vector &radians)
{
    Transform(x, y, z, scale[0], scale[1], scale[2], radians[0], radians[1], radians[2]);
}

void Model3D::Transform(const math::Vector &center, const math::Vector &scale, const math::Vector &radians)
{
    Transform(center[0], center[1], center[2], scale[0], scale[1], scale[2], radians[0], radians[1], radians[2]);
}

void Model3D::Draw()
{
    double red = color_.get_red() / 255.0;
    double green = color_.get_green() / 255.0;
    double blue = color_.get_blue() / 255.0;
    double alpha = color_.get_alpha() / 255.0;

    glColor4d(red, green, blue, alpha);
    glBegin(GL_POLYGON);
    for (int i = 0; i < points_.get_rows(); i++)
        glVertex3d(points_[i][0], points_[i][1], points_[i][2]);

    glEnd();
}

Vector Model3D::get_angle() const
{
    return angle_;
}

void Model3D::ValidateMatrix(const math::Matrix &matrix)
{
    if (matrix.get_columns() != 3)
    {
        throw std::invalid_argument("The matrix must have 3 columns.");
    }
}