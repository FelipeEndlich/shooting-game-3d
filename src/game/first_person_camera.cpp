#include "./first_person_camera.hpp"
#include "./camera.hpp"
#include "../math/vector.hpp"
#include <GL/glut.h>
#include <cmath>

using math::Vector;
using shoot_and_jump::Camera;
using shoot_and_jump::FirstPersonCamera;

FirstPersonCamera::FirstPersonCamera(const math::Vector &character_position)
    : Camera()
{
    eye_ = Vector::ThreeDimPoint(character_position[0], character_position[1], character_position[2]);

    Vector center = Vector::ThreeDimPoint(character_position[0] + 1, character_position[1], character_position[2]);

    center_ = Vector::ThreeDimPoint(center[0], center[1], center[2]);
    up_ = Vector::ThreeDimPoint(0, -1, 0);
}

void FirstPersonCamera::Move(const math::Vector &movement)
{
    eye_ += movement;
    center_ += movement;
}

void FirstPersonCamera::Rotate(const math::Vector &angles)
{
    double rho_squared, tan_theta, cos_phi;
    double rho, theta, phi;
    double x, y, z;
    x = center_[0];
    y = center_[1];
    z = center_[2];

    rho_squared = pow(x, 2) + pow(y, 2) + pow(z, 2);
    tan_theta = y / x;
    cos_phi = z / sqrt(rho_squared);

    rho = sqrt(rho_squared);
    theta = atan(tan_theta) - angles[0];
    phi = acos(cos_phi) + asin(angles[1]);

    center_[0] = rho * sin(phi) * cos(theta);
    center_[1] = rho * sin(phi) * sin(theta);
    center_[2] = rho * cos(phi);
}