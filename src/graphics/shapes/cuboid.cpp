#include "cuboid.hpp"

#include <stdexcept>

#include <GL/glut.h>

#include "./model.hpp"
#include "./../color/rgba.hpp"
#include "./../../math/matrix.hpp"
#include "./../../math/vector.hpp"

#include <iostream>
#include <memory>

using ::graphics::color::RGBA;
using ::graphics::shapes::Cuboid;
using ::graphics::shapes::Model;
using ::graphics::shapes::Model3D;
using ::math::Matrix;
using ::math::Vector;

Cuboid::Cuboid(double width, double height, double depth)
    : Model3D()
{
    this->width = width;
    this->height = height;
    this->depth = depth;

    this->initial_position = math::Vector::Zero(3);

    BuildPoints(width, height, depth, Vector::Zero(3));
}

Cuboid::Cuboid(double width, double height, double depth, const math::Vector &initial_position)
    : Model3D()
{
    this->width = width;
    this->height = height;
    this->depth = depth;
    this->initial_position = initial_position;

    BuildPoints(width, height, depth, initial_position);
}

math::Vector Cuboid::get_center_position() const
{
    return math::Vector::ThreeDimPoint(
        this->initial_position[0] + this->width / 2,
        this->initial_position[1] - this->height / 2,
        this->initial_position[2] + this->depth / 2);
}

void Cuboid::BuildPoints(double width, double height, double depth, const math::Vector &initial_position)
{
}

void Cuboid::Draw()
{
    double z0;
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0);
    this->__draw_face(z0 = this->initial_position[2]);
    glColor3f(0, 1, 0);
    this->__draw_face(z0 + this->depth);
    glColor3f(0, 0, 1);
    this->__draw_interface();
    glEnd();
}

void Cuboid::__draw_interface()
{
    // Start points
    double x0, y0, z0;
    x0 = this->initial_position[0];
    y0 = this->initial_position[1];
    z0 = this->initial_position[2];

    // End points
    double x1, y1, z1;
    x1 = x0 + this->width;
    y1 = y0 - this->height;
    z1 = z0 + this->depth;

    this->__draw_line(x0, y0, z0, x0, y0, z1);
    this->__draw_line(x1, y0, z0, x1, y0, z1);
    this->__draw_line(x0, y1, z0, x0, y1, z1);
    this->__draw_line(x1, y1, z0, x1, y1, z1);
}

void Cuboid::__draw_face(double z)
{
    double x0, y0, x1, y1;
    x0 = this->initial_position[0];
    y0 = this->initial_position[1];

    x1 = x0 + this->width;
    y1 = y0 - this->height;

    // Drawing the faces' lines
    this->__draw_line(x0, y0, z, x1, y0, z);
    this->__draw_line(x1, y0, z, x1, y1, z);
    this->__draw_line(x1, y1, z, x0, y1, z);
    this->__draw_line(x0, y1, z, x0, y0, z);
}

void Cuboid::__draw_line(double xi, double yi, double zi, double xf, double yf, double zf)
{
    glVertex3f(xi, yi, zi);
    glVertex3f(xf, yf, zf);
}