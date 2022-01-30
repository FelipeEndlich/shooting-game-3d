#pragma once

#include "./model_2d.hpp"

namespace graphics::shapes
{
    class Circle : public Model2D
    {
    public:
        Circle();
        Circle(const math::Vector &origin, double radius);
        Circle(const math::Vector &origin, double radius, const graphics::color::RGBA &color);
        Circle(const Circle &other);
        Circle(const Circle &&other);
        virtual ~Circle() = default;

        Circle &operator=(const Circle &other);
        Circle &operator=(const Circle &&other);

        double get_radius() const;

    protected:
        double radius_;

        void BuildPoints(const math::Vector &origin, double radius);

    private:
        static inline double segments_ = 32;
    };
}
