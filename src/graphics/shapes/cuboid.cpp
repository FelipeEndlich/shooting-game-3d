#include "cuboid.hpp"

using ::graphics::color::RGBA;
using ::graphics::shapes::Cuboid;
using ::math::Matrix;
using ::math::Vector;

#pragma region Constructor and Destructor
Cuboid::Cuboid()
    : Model3D()
{
    color_ = RGBA();
    angle_ = 0;
    BuildPoints(Vector::Zero(3), 0, 0);
}

Cuboid::Cuboid(const Vector &origin, double width, double height)
    : Model3D()
{
    color_ = RGBA();
    width_ = width;
    height_ = height;

    angle_ = 0;

    BuildPoints(origin, width, height);
}

Cuboid::Cuboid(const Vector &origin, double width, double height, const RGBA &color)
    : Model3D()
{
    color_ = color;
    width_ = width;
    height_ = height;
    angle_ = 0;
    BuildPoints(origin, width, height);
}

Cuboid::Cuboid(const Cuboid &other)
    : Model3D(other)
{
    *this = other;
}

Cuboid::Cuboid(const Cuboid &&other)
    : Model3D(other)
{
    *this = other;
}
#pragma endregion // Constructor and Destructor

#pragma region Operator Overloads
Cuboid &Cuboid::operator=(const Cuboid &other)
{
    points_ = other.points_;
    color_ = other.color_;
    width_ = other.width_;
    height_ = other.height_;
    angle_ = other.angle_;
    return *this;
}

Cuboid &Cuboid::operator=(const Cuboid &&other)
{
    points_ = other.points_;
    color_ = other.color_;
    width_ = other.width_;
    height_ = other.height_;
    angle_ = other.angle_;
    return *this;
}
#pragma endregion // Operator Overloads

#pragma region Private Methods
void Cuboid::BuildPoints(const Vector &origin, double width, double height)
{
    points_ = Matrix::Zero(8, 3);
    this->width_ = width;
    this->height_ = height;

    // points_[0][0] = origin[0];
    // points_[0][1] = origin[1];

    // points_[1][0] = origin[0] + width;
    // points_[1][1] = origin[1];

    // points_[2][0] = origin[0] + width;
    // points_[2][1] = origin[1] + height;

    // points_[3][0] = origin[0];
    // points_[3][1] = origin[1] + height;

    double x0, y0, z0;
    x0 = origin[0];
    y0 = origin[1];
    z0 = origin[2];

    // Final points
    double depth = 1;
    double x1, y1, z1;
    x1 = width + x0;
    y1 = height + y0;
    z1 = depth + z0;

    // Four front points and four back points
    // Front: f_1, f_2, f_3, f_4
    // Back:  b_1, b_2, b_3, b_4
    // 8 total points
    points_ = Matrix::Zero(8, 3);

    points_[0][0] = x0, points_[0][1] = y0, points_[0][2] = z0; // f_1
    points_[1][0] = x1, points_[1][1] = y0, points_[1][2] = z0; // f_2
    points_[2][0] = x1, points_[2][1] = y1, points_[2][2] = z0; // f_3
    points_[3][0] = x0, points_[3][1] = y1, points_[3][2] = z0; // f_4

    points_[4][0] = x0, points_[4][1] = y0, points_[4][2] = z1; // b_1
    points_[5][0] = x1, points_[5][1] = y0, points_[5][2] = z1; // b_2
    points_[6][0] = x1, points_[6][1] = y1, points_[6][2] = z1; // b_3
    points_[7][0] = x0, points_[7][1] = y1, points_[7][2] = z1; // b_4
}
#pragma endregion // Private Methods

#pragma region Getters and Setters
double Cuboid::get_width() const
{
    return width_;
}

double Cuboid::get_height() const
{
    return height_;
}
#pragma endregion // Getters and Setters

Vector Cuboid::get_center_position() const
{
    return Vector(points_[0] + points_[1] + points_[2] + points_[3]) / 4;
}