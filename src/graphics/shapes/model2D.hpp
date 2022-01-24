#pragma once

#include "./model.hpp"

namespace graphics
{
    namespace shapes
    {
        class Model2D : public Model
        {
        public:
            Model2D();
            Model2D(const math::Matrix &matrix);
            Model2D(const math::Matrix &matrix, const graphics::color::RGBA &color);
            Model2D(const Model2D &other);
            Model2D(const Model2D &&other);
            virtual ~Model2D();

            virtual void translate(const math::Vector &vector);
            virtual void scale(const math::Vector center, const math::Vector &vector);
            virtual void rotate(const math::Vector center, double radians);
            virtual void transform(const math::Matrix &matrix);
            virtual void transform(const math::Vector center, const math::Vector &translate, const math::Vector &scale, double radians);

            virtual void draw();
        private:
            void validateMatrix(const math::Matrix &matrix);
        };

    }
}