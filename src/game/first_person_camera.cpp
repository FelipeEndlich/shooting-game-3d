#include "./first_person_camera.hpp"
#include "./camera.hpp"
#include "../math/vector.hpp"
#include <GL/glut.h>
#include <cmath>
#include <iostream>

using math::Vector;
using shoot_and_jump::Camera;
using shoot_and_jump::FirstPersonCamera;

FirstPersonCamera::FirstPersonCamera(const math::Vector &character_position)
    : Camera()
{
    eye_ = Vector::ThreeDimPoint(character_position[0], character_position[1], character_position[2]);

    Vector center = Vector::ThreeDimPoint(character_position[0] + 1, character_position[1], character_position[2]);

    center_ = Vector::ThreeDimPoint(center[0], center[1], center[2]);
    up_ = Vector::ThreeDimPoint(0, 0, 1).CrossProduct(center_ - eye_);
    up_[1] = -up_[1];
}

void FirstPersonCamera::Move(physic::Direction direction, double increment)
{
    switch (direction)
    {
    case physic::Direction::kLeft:
    {
        double x = sin(angle_) * increment;
        double y = 0;
        double z = cos(angle_) * increment;
        Vector vec = Vector::ThreeDimPoint(x, y, z);

        center_ += vec;
        eye_ += vec;
    }
    break;

    case physic::Direction::kRight:
    {
        double x = sin(angle_) * increment;
        double y = 0;
        double z = cos(angle_) * increment;
        Vector vec = Vector::ThreeDimPoint(x, y, z);

        center_ -= vec;
        eye_ -= vec;
    }
    break;

    case physic::Direction::kForward:
    {
        double x = cos(angle_) * increment;
        double y = 0;
        double z = sin(angle_) * increment;
        Vector vec = Vector::ThreeDimPoint(x, y, z);

        center_ += vec;
        eye_ += vec;
    }
    break;

    case physic::Direction::kBackward:
    {
        double x = cos(angle_) * increment;
        double y = 0;
        double z = sin(angle_) * increment;
        Vector vec = Vector::ThreeDimPoint(x, y, z);

        center_ -= vec;
        eye_ -= vec;
    }

    default:
        break;
    }
}

void FirstPersonCamera::Rotate(const math::Vector &angles)
{
    double rho_squared, tan_theta, cos_phi;
    double rho, theta, phi;
    double x, y, z;
    x = center_[0] - eye_[0];
    y = center_[1] - eye_[1];
    z = center_[2] - eye_[2];

    rho_squared = pow(x, 2) + pow(y, 2) + pow(z, 2);
    tan_theta = y / x;
    cos_phi = z / sqrt(rho_squared);

    rho = sqrt(rho_squared);
    theta = atan(tan_theta) - angles[0];
    phi = acos(cos_phi) + angles[1];

    double base_phi, base_theta;
    base_phi = phi / M_PI - 0.5;
    base_theta = theta / M_PI;

    if (!(-0.5 < base_phi && base_phi < 0.5) || !(-0.2 < base_theta && base_theta < 0.2))
        return;

    center_[0] = rho * sin(phi) * cos(theta) + eye_[0];
    center_[1] = rho * sin(phi) * sin(theta) + eye_[1];
    center_[2] = rho * cos(phi) + eye_[2];

    up_ = Vector::ThreeDimPoint(0, 0, 1).CrossProduct(center_ - eye_);
    up_[1] = -up_[1];
}