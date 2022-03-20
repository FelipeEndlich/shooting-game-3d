#include "./first_person_camera.hpp"
#include "./camera.hpp"
#include "../math/vector.hpp"
#include <GL/glut.h>

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
}