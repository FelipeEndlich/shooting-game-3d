#include "gun.hpp"

#include "../../physics/rigid_body.hpp"
#include "../../math/vector.hpp"
#include "../color/rgba.hpp"
#include "../color/rgba_factory.hpp"
#include "../shapes/rectangle.hpp"
#include "./character/character.hpp"

using ::graphics::color::RGBA;
using ::graphics::color::RGBAFactory;
using ::graphics::elements::Gun;
using ::graphics::elements::character::Character;
using ::graphics::shapes::Rectangle;
using ::math::Vector;

Gun::Gun(Vector &initial_position, double width, double height)
    : RigidBody(2)
{
    Vector body_initial_position = initial_position;
    body_initial_position[1] -= height / 2;
    body_ = new Rectangle(body_initial_position, width, height, RGBAFactory::get_color("black"));

    double barrel_width = body_->get_width() / 2;
    double barrel_height = body_->get_height() / 2;
    Vector barrel_initial_position = body_->get_center_position();
    barrel_initial_position[0] += width / 2;
    barrel_initial_position[1] -= barrel_height / 3;
    barrel_ = new Rectangle(barrel_initial_position, barrel_width, barrel_height, RGBAFactory::get_color("black"));

    double grip_width = body_->get_width() / 4;
    double grip_height = body_->get_height();
    Vector grip_initial_position = body_->get_center_position();
    grip_initial_position[0] -= (body_->get_width() - grip_width) / 2;
    grip_initial_position[1] += body_->get_height() / 2;
    grip_ = new Rectangle(grip_initial_position, grip_width, grip_height, RGBAFactory::get_color("black"));

    double magazine_width = body_->get_width() / 4;
    double magazine_height = body_->get_height() / 2;
    Vector magazine_initial_position = body_->get_center_position();
    magazine_initial_position[0] -= (body_->get_width() - magazine_width * 4) / 2;
    magazine_initial_position[1] += body_->get_height() / 2;
    magazine_ = new Rectangle(magazine_initial_position, magazine_width, magazine_height, RGBAFactory::get_color("black"));
}

Gun::~Gun()
{
    delete body_;
    delete barrel_;
    delete grip_;
    delete magazine_;
}

void Gun::Shoot()
{
}

void Gun::Render()
{
    body_->Draw();
    barrel_->Draw();
    grip_->Draw();
    magazine_->Draw();
}

void Gun::Translate(math::Vector &translation, bool translate_position)
{
    body_->Translate(translation);
    barrel_->Translate(translation);
    grip_->Translate(translation);
    magazine_->Translate(translation);

    if (translate_position)
        position_ += translation;
}

void Gun::Scale(math::Vector &scale, double sx, double sy)
{
    body_->Scale(scale, sx, sy);
    barrel_->Scale(scale, sx, sy);
    grip_->Scale(scale, sx, sy);
    magazine_->Scale(scale, sx, sy);
}

Vector Gun::get_position()
{
    return position_;
}

double Gun::get_width()
{
    return width_;
}

double Gun::get_height()
{
    return height_;
}