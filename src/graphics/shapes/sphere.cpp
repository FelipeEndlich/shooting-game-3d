#include "sphere.hpp"

#include <iostream>
#include <cmath>

#include <GL/glut.h>

#include "model_3d.hpp"
#include "../color/rgba.hpp"
#include "../../math/vector.hpp"
#include "../../math/matrix.hpp"

using ::graphics::color::RGBA;
using ::graphics::shapes::Model3D;
using ::graphics::shapes::Sphere;
using ::math::Matrix;
using ::math::Vector;
using ::std::cout;
using ::std::endl;

Sphere::Sphere(double radius)
    : Model3D(), radius_(radius)
{
    BuildPoints(Vector::Zero(3));
}

Sphere::Sphere(double radius, const Vector &initial_position)
    : Model3D(), radius_(radius)
{
    BuildPoints(initial_position);
}

Sphere::Sphere(double radius, const Vector &initial_position, const RGBA &color)
    : Model3D(), radius_(radius)
{
    color_ = color;
    BuildPoints(initial_position);
}

Vector Sphere::get_center_position() const
{
}

void Sphere::BuildPoints(const Vector &initial_position)
{
    points_ = Matrix::Zero(sector_ * stacks_ + 1, 3);
    for (int i = 0; i < sector_; i++)
    {
        for (int j = 0; j < stacks_ + 1; j++)
        {
            double theta = 2 * M_PI * i / sector_;
            double phi = M_PI / 2 - M_PI * j / stacks_;

            Vector point(3);
            point[0] = radius_ * cos(phi) * cos(theta);
            point[1] = radius_ * cos(phi) * sin(theta);
            point[2] = radius_ * sin(phi);

            points_[i * stacks_ + j] = point + initial_position;
        }
    }
}

void Sphere::Draw()
{
    double red = color_.get_red() / 255.0;
    double green = color_.get_green() / 255.0;
    double blue = color_.get_blue() / 255.0;
    double alpha = color_.get_alpha() / 255.0;

    glColor4d(red, green, blue, alpha);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < sector_; i++)
    {
        for (int j = 0; j < stacks_; j++)
        {
            int i1 = i * stacks_ + j;
            int i2 = i1 + 1;
            int i3 = i == sector_ - 1 ? j : (i + 1) * stacks_ + j;
            int i4 = i3 + 1;

            if (j == stacks_ - 1)
            {
                i2 = sector_ * stacks_;
                i4 = sector_ * stacks_;
            }

            glVertex3d(points_[i1][0], points_[i1][1], points_[i1][2]);
            glVertex3d(points_[i2][0], points_[i2][1], points_[i2][2]);
            glVertex3d(points_[i3][0], points_[i3][1], points_[i3][2]);

            glVertex3d(points_[i2][0], points_[i2][1], points_[i2][2]);
            glVertex3d(points_[i3][0], points_[i3][1], points_[i3][2]);
            glVertex3d(points_[i4][0], points_[i4][1], points_[i4][2]);
        }
    }
    glEnd();
}