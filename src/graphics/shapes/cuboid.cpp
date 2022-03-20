#include "cuboid.hpp"

#include <GL/glut.h>

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
    BuildPoints(Vector::Zero(3), 0, 0, 1 /* depth as 1 */);
}

Cuboid::Cuboid(const Vector &origin, double width, double height)
    : Model3D()
{
    color_ = RGBA();
    width_ = width;
    height_ = height;

    angle_ = 0;

    double depth = 5;
    BuildPoints(origin, width, height, depth);
}

Cuboid::Cuboid(const Vector &origin, double width, double height, const RGBA &color)
    : Model3D()
{
    color_ = color;
    width_ = width;
    height_ = height;
    angle_ = 0;

    double depth = 5;
    BuildPoints(origin, width, height, depth);
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
void Cuboid::BuildPoints(const Vector &origin, double width, double height, double depth)
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

void Cuboid::__draw_quad_face(math::Vector p1, math::Vector p2, math::Vector p3, math::Vector p4)
{
    double x, y, z;

    auto update_coords = [](math::Vector p, double *x, double *y, double *z)
    {
        *x = p[0];
        *y = p[1];
        *z = p[2];
    };

    std::vector<math::Vector> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);

    for (math::Vector p : points)
    {
        update_coords(p, &x, &y, &z);
        glVertex3f(x, y, z);
    }
}

void Cuboid::__draw_interface()
{
    // Start points
    double x0, y0, z0;
    x0 = this->points_[0][0];
    y0 = this->points_[0][1];
    z0 = this->points_[0][2];

    // End points
    double x1, y1, z1;
    x1 = x0 + this->width_;
    y1 = y0 - this->height_;
    z1 = z0 + this->depth_;

    this->__draw_line(x0, y0, z0, x0, y0, z1);
    this->__draw_line(x1, y0, z0, x1, y0, z1);
    this->__draw_line(x0, y1, z0, x0, y1, z1);
    this->__draw_line(x1, y1, z0, x1, y1, z1);
}

void Cuboid::__draw_face(double z)
{
    double x0, y0, x1, y1;
    x0 = this->points_[0][0];
    y0 = this->points_[0][1];

    x1 = x0 + this->width_;
    y1 = y0 - this->height_;

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

void Cuboid::Draw()
{
    double red = color_.get_red() / 255.0;
    double green = color_.get_green() / 255.0;
    double blue = color_.get_blue() / 255.0;
    double alpha = color_.get_alpha() / 255.0;

    // Start points
    double x0, y0, z0;
    x0 = points_[0][0], y0 = points_[0][1], z0 = points_[0][2];

    // Final points
    double x1, y1, z1;
    x1 = points_[6][0], y1 = points_[6][1], z1 = points_[6][2];

    glBegin(GL_QUADS);

    // Front face
    glColor4d((red + 0.5) / 2, green, blue, alpha);
    this->__draw_quad_face(
        math::Vector::ThreeDimPoint(x0, y0, z0),
        math::Vector::ThreeDimPoint(x1, y0, z0),
        math::Vector::ThreeDimPoint(x1, y1, z0),
        math::Vector::ThreeDimPoint(x0, y1, z0));

    // Back face
    glColor4d(red, (green + 0.5) / 2, blue, alpha);
    this->__draw_quad_face(
        math::Vector::ThreeDimPoint(x0, y0, z1),
        math::Vector::ThreeDimPoint(x1, y0, z1),
        math::Vector::ThreeDimPoint(x1, y1, z1),
        math::Vector::ThreeDimPoint(x0, y1, z1));

    // Right face
    glColor4d(red, green, (blue + 0.5) / 2, alpha);
    __draw_quad_face(
        math::Vector::ThreeDimPoint(x1, y0, z0),
        math::Vector::ThreeDimPoint(x1, y1, z0),
        math::Vector::ThreeDimPoint(x1, y1, z1),
        math::Vector::ThreeDimPoint(x1, y0, z1));

    // Left face
    glColor4d((red + 0.5) / 2, green, blue, alpha);
    __draw_quad_face(
        math::Vector::ThreeDimPoint(x0, y0, z0),
        math::Vector::ThreeDimPoint(x0, y1, z0),
        math::Vector::ThreeDimPoint(x0, y1, z1),
        math::Vector::ThreeDimPoint(x0, y0, z1));

    // Upper face
    glColor4d(red, (green + 0.5) / 2, blue, alpha);
    __draw_quad_face(
        math::Vector::ThreeDimPoint(x0, y1, z0),
        math::Vector::ThreeDimPoint(x1, y1, z0),
        math::Vector::ThreeDimPoint(x1, y1, z1),
        math::Vector::ThreeDimPoint(x0, y1, z1));

    // Bottom face
    glColor4d(red, green, (blue + 0.5) / 2, alpha);
    __draw_quad_face(
        math::Vector::ThreeDimPoint(x0, y0, z0),
        math::Vector::ThreeDimPoint(x1, y0, z0),
        math::Vector::ThreeDimPoint(x1, y0, z1),
        math::Vector::ThreeDimPoint(x0, y0, z1));

    glEnd();
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