#include "bullet.hpp"

#include <iostream>

#include "../../physics/rigid_body.hpp"
#include "../../math/vector.hpp"
#include "../shapes/circle.hpp"
#include "../color/rgba_factory.hpp"

using ::graphics::color::RGBAFactory;
using ::graphics::elements::Bullet;
using ::graphics::shapes::Circle;
using ::math::Vector;
using ::physic::RigidBody;
using ::std::cout;
using ::std::endl;

Bullet::Bullet(const Vector &initial_position, const Vector &initial_velocity, double radius)
    : RigidBody(2)
{
    shape_ = new Circle(initial_position, radius, RGBAFactory::get_color("black"));
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
