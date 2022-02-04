#include "cuboid.hpp"

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
    this->initial_position = new math::Vector(3);

    // Setting initial position
    for (int i = 0; i < 3; i++)
        this->initial_position[i] = 0;

    BuildPoints(width, height, depth, Vector::Zero(3));
}

Cuboid::Cuboid(double width, double height, double depth, const math::Vector &initial_position)
    : Model3D()
{
    this->width = width;
    this->height = height;
    this->depth = depth;
    this->initial_position = new math::Vector(initial_position.get_dimension());

    // Setting initial position
    for (int i = 0; i < initial_position.get_dimension(); i++)
        this->initial_position[i] = initial_position[i];

    BuildPoints(width, height, depth, initial_position);
}

math::Vector Cuboid::get_center_position() const
{
    return Vector::Zero(3);
}

void Cuboid::BuildPoints(double width, double height, double depth, const math::Vector &initial_position)
{

}