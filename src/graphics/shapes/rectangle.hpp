#pragma once

#include "./model_2d.hpp"

namespace graphics::shapes
{
    class Rectangle : public Model2D
    {
    public:
        Rectangle();
        Rectangle(const math::Vector &origin, double width, double height);
        Rectangle(const math::Vector &origin, double width, double height, const graphics::color::RGBA &color);
        Rectangle(const Rectangle &other);
        Rectangle(const Rectangle &&other);
        ~Rectangle() = default;

        Rectangle &operator=(const Rectangle &other);
        Rectangle &operator=(const Rectangle &&other);

        double get_width() const;
        double get_height() const;

    private:
        double width_;
        double height_;

        void BuildPoints(const math::Vector &origin, double width, double height);
    };
}