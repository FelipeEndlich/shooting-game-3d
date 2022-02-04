#include "cuboid.hpp"

#include "model_3d.hpp"

#include <stdexcept>

#include <GL/glut.h>

#include "./model.hpp"
#include "./../color/rgba.hpp"
#include "./../../math/matrix.hpp"
#include "./../../math/vector.hpp"

using ::graphics::color::RGBA;
using ::graphics::shapes::Model;
using ::graphics::shapes::Model3D;
using ::graphics::shapes::Cuboid;
using ::math::Matrix;
using ::math::Vector;

Cuboid::Cuboid(double width, double height, double depth)
    : Model3D()
{
    this->width = width;
    this->height = height;
    this->depth = depth;
}

Cuboid::Cuboid(double width, double height, double depth, const math::Matrix& matrix)
    : Model3D(matrix)
{
    this->width = width;
    this->height = height;
    this->depth = depth;
}

void Cuboid::Draw()
{
    glBegin(GL_LINES);

    glEnd();
}