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

void Cuboid::DrawLines()
{
    double z0;
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    this->__draw_face(z0 = this->initial_position[2]);
    glColor3f(0, 1, 0);
    this->__draw_face(z0 + this->depth);
    glColor3f(0, 0, 1);
    this->__draw_interface();
    glEnd();
}

void Cuboid::Draw() {
    // Start points
    double x0, y0, z0;
    x0 = this->initial_position[0];
    y0 = this->initial_position[1];
    z0 = this->initial_position[2];

    // Final points
    double x1, y1, z1;
    x1 = this->width + x0;
    y1 = y0 - this->height;
    z1 = this->depth + z0;

    glBegin(GL_QUADS);

    // Front face
    glColor3f(0, 0, 1);
    this->__draw_quad_face(
        math::Vector::ThreeDimPoint(x0, y0, z0),
        math::Vector::ThreeDimPoint(x1, y0, z0),
        math::Vector::ThreeDimPoint(x1, y1, z0),
        math::Vector::ThreeDimPoint(x0, y1, z0)
    );

    // Back face
    glColor3f(0, 1, 0);
    this->__draw_quad_face(
        math::Vector::ThreeDimPoint(x0, y0, z1),
        math::Vector::ThreeDimPoint(x1, y0, z1),
        math::Vector::ThreeDimPoint(x1, y1, z1),
        math::Vector::ThreeDimPoint(x0, y1, z1)
    );

    // Right face
    glColor3f(0, 1, 1);
    this->__draw_quad_face(
        math::Vector::ThreeDimPoint(x1, y0, z0),
        math::Vector::ThreeDimPoint(x1, y1, z0),
        math::Vector::ThreeDimPoint(x1, y1, z1),
        math::Vector::ThreeDimPoint(x1, y0, z1)
    );

    // Left face
    glColor3f(1, 0, 0);
    this->__draw_quad_face(
        math::Vector::ThreeDimPoint(x0, y0, z0),
        math::Vector::ThreeDimPoint(x0, y1, z0),
        math::Vector::ThreeDimPoint(x0, y1, z1),
        math::Vector::ThreeDimPoint(x0, y0, z1)
    );

    // Upper face
    glColor3f(1, 0, 1);
    this->__draw_quad_face(
        math::Vector::ThreeDimPoint(x0, y1, z0),
        math::Vector::ThreeDimPoint(x1, y1, z0),
        math::Vector::ThreeDimPoint(x1, y1, z1),
        math::Vector::ThreeDimPoint(x0, y1, z1)
    );

    // Bottom face
    glColor3f(1, 1, 0);
    this->__draw_quad_face(
        math::Vector::ThreeDimPoint(x0, y0, z0),
        math::Vector::ThreeDimPoint(x1, y0, z0),
        math::Vector::ThreeDimPoint(x1, y0, z1),
        math::Vector::ThreeDimPoint(x0, y0, z1)
    );


    glEnd();
}

void Cuboid::__draw_quad_face(math::Vector p1, math::Vector p2, math::Vector p3, math::Vector p4)
{
    double x, y, z;

    auto update_coords = [] (math::Vector p, double *x, double *y, double *z) {
        *x = p[0]; *y = p[1]; *z = p[2];
    };

    std::vector<math::Vector> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);

    for (math::Vector p : points) {
        update_coords(p, &x, &y, &z);
        glVertex3f(x, y, z);
    }
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