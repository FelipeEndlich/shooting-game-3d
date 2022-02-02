#pragma once

#include "./../../math/matrix.hpp"
#include "./../color/rgba.hpp"

namespace graphics::shapes
{
    class Model
    {
    public:
        Model();
        Model(const math::Matrix &matrix);
        Model(const math::Matrix &matrix, const graphics::color::RGBA &color);
        Model(const Model &other);
        Model(const Model &&other);
        virtual ~Model() = default;

        Model &operator=(const Model &other);
        Model &operator=(const Model &&other);

        virtual void Translate(const math::Vector &vector) = 0;
        virtual void Scale(const math::Vector &center, const math::Vector &vector) = 0;
        virtual void Rotate(const math::Vector &center, double radians) = 0;
        virtual void Transform(const math::Matrix &matrix) = 0;
        virtual void Transform(const math::Vector &center, const math::Vector &scale, double radians) = 0;

        virtual void Draw() = 0;

    protected:
        math::Matrix points_;
        color::RGBA color_;
    };
}