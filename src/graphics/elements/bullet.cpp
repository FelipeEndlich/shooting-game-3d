#include "bullet.hpp"

#include <iostream>

#include "../../physics/rigid_body.hpp"
#include "../../physics/icollidable.hpp"
#include "../../math/vector.hpp"
#include "../shapes/circle.hpp"
#include "../color/rgba_factory.hpp"

using ::graphics::color::RGBAFactory;
using ::graphics::elements::Bullet;
using ::graphics::shapes::Circle;
using ::math::Vector;
using ::physic::ICollidable;
using ::physic::RigidBody;
using ::std::cout;
using ::std::endl;

Bullet::Bullet(const Vector &initial_position, const Vector &initial_velocity, double radius)
    : RigidBody(2)
{
    shape_ = new Circle(initial_position, radius, RGBAFactory::get_color("red"));
    position_ = initial_position;
    velocity_ = initial_velocity;
    acceleration_ = Vector::Zero(2);
    external_force_ = get_weight() * -1;
}

Bullet::~Bullet()
{
    delete shape_;
}

void Bullet::Render()
{
    shape_->Draw();
}

void Bullet::Update(double delta_time)
{
    Vector old_position = position_;
    RigidBody::Update(delta_time);
    Vector position = position_;
    shape_->Translate(position - old_position);
}

Vector Bullet::get_position()
{
    Vector position = position_;
    position[0] -= shape_->get_radius();
    position[1] -= shape_->get_radius();
    return position;
}

double Bullet::get_width()
{
    return shape_->get_radius() * 2;
}

double Bullet::get_height()
{
    return shape_->get_radius() * 2;
}

void Bullet::ProcessCollision(ICollidable *collidable)
{
    cout << "Bullet::ProcessCollision" << endl;
}