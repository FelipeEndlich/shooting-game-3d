#include "cuboid.hpp"

#include "model_3d.hpp"

#include <stdexcept>

#include <GL/glut.h>

#include "./model.hpp"
#include "./../color/rgba.hpp"
#include "./../../math/matrix.hpp"
#include "./../../math/vector.hpp"

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

    BuildPoints(width, height, depth, Vector::Zero(3));
}

Cuboid::Cuboid(double width, double height, double depth, const math::Vector &initial_position)
    : Model3D()
{
    this->width = width;
    this->height = height;
    this->depth = depth;

    BuildPoints(width, height, depth, initial_position);
}

void Cuboid::BuildPoints(double width, double height, double depth, const math::Vector &initial_position)
{
}