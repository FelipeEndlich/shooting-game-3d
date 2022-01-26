#pragma once

#include "./model.hpp"

namespace graphics::shapes
{
    class Model2D : public Model
    {
    public:
        Model2D();
        Model2D(const math::Matrix &matrix);
        Model2D(const math::Matrix &matrix, const graphics::color::RGBA &color);
        Model2D(const Model2D &other);
        Model2D(const Model2D &&other);
        virtual ~Model2D() = default;

        virtual void Translate(const math::Vector &vector);
        virtual void Scale(const math::Vector &center, const math::Vector &vector);
        virtual void Rotate(const math::Vector &center, double radians);
        virtual void Transform(const math::Matrix &matrix);
        virtual void Transform(const math::Vector &center, const math::Vector &scale, double radians);

        virtual void Draw();

    private:
        void ValidateMatrix(const math::Matrix &matrix);
    };
}