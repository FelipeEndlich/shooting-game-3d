#include "camera.hpp"
#include "../math/vector.hpp"
#include <GL/glut.h>

using ::math::Vector;
using ::shoot_and_jump::Camera;

Camera::Camera()
{
    this->eye_ = Vector::Zero(3);
    this->center_ = Vector::Zero(3);
    this->up_ = Vector::Zero(3);
}

void Camera::Run()
{
    gluLookAt(
        eye_[0], eye_[1], eye_[2],
        center_[0], center_[1], center_[2],
        up_[0], up_[1], up_[2]);
}

double Camera::get_x() const
{
    return eye_[0];
}

double Camera::get_y() const
{
    return eye_[1];
}

double Camera::get_z() const
{
    return eye_[0];
}