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

Matrix rotationMatrix(double phi, double psi, double theta) {

    auto r_x = [] (double phi) {
        Matrix rot = Matrix::Identity(4, 4);
        rot[1][1] = cos(phi);  rot[1][2] = -sin(phi);
        rot[2][1] = sin(phi);  rot[2][2] = cos(phi);
        return rot;
    };

    /*
    auto r_y = [] (double psi) {
        return Matrix::FourDimMatrix(
            cos(psi),        0,         -sin(psi), 0,
                    0,        1,                0, 0,
            sin(psi),        0,         cos(psi), 0,
            0,                0,                0, 1
        );
    };


    auto r_z = [] (double theta) {
        return Matrix::FourDimMatrix(
            cos(theta),  sin(theta), 0, 0,
            -sin(theta),  cos(theta), 0, 0,
                     0,           0, 1, 0,
                     0,           0, 0, 1
        );
    }; */

    return r_x(phi);

}

void Model3D::Transform(double x, double y, double z, double sx, double sy, double sz, double phi, double psi, double theta)
{
    // Phi, Psi and Theta must be in radians
    //Vector point;

    // Centering the mode
    for (int i = 0; i < points_.get_rows(); i++) {
        points_[i][0] -= x / 2;
        points_[i][1] -= y / 2;
        points_[i][2] -= z / 2;
    }

    // Rotating the model
    auto r_m = rotationMatrix(phi, psi, theta);

    // Translating the model
    /*Matrix t_m;
    t_m = Matrix::FourDimMatrix(
        1, 0, 0, sx + x,
        0, 1, 0, sy + y,
        0, 0, 1, sy + z,
        0, 0, 0, 1
    );*/

    //Matrix tf_m;
    //tf_m = t_m * r_m;

    for (int i = 0; i < points_.get_rows(); i++) {
        for (int j = 0; j < 3; j++)
            printf("%lf ", points_[i][j]);
        printf("/n");
        Vector aug_points = Vector::Zero(4);
        for (int j = 0; j < 3; j++)
            aug_points[j] = points_[i][j];
        aug_points[3] = 1;
        aug_points = r_m * aug_points;
        for (int j = 0; j < 3; j++)
            points_[i][j] = aug_points[j];
        /*
        double x, y, z;
        x = points_[i][0];
        y = points_[i][1];
        z = points_[i][2];

        double polar_radius, polar_delta, polar_theta;
        polar_radius = sqrt(x * x + y * y + z * z);
        polar_delta = atan(z / sqrt(z *x + y * y));
        polar_theta = atan(y / z);

        polar_delta += theta;
        polar_theta += phi;

        points_[i][0] = polar_radius * cos(polar_delta) * cos(polar_theta);
        points_[i][1] = polar_radius * cos(polar_delta) * sin(polar_theta);
        points_[i][2] = polar_radius * sin(polar_delta);
        */
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