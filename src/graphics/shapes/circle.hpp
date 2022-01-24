#pragma once

#include "./model2D.hpp"

namespace graphics
{
    namespace shapes
    {
        class Circle : public Model2D
        {
        public:
            Circle();
            Circle(const math::Vector &origin, double radius);
            Circle(const math::Vector &origin, double radius, const graphics::color::RGBA &color);
            Circle(const Circle &other);
            Circle(const Circle &&other);
            ~Circle() = default;

            Circle &operator=(const Circle &other);
            Circle &operator=(const Circle &&other);

        private:
            double radius;
            static inline double segments = 32;

            void buildPoints(const math::Vector &origin, double radius);
        };
    }
}
