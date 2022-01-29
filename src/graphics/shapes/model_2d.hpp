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

        virtual double get_angle() const;
        math::Vector get_center_position() const;
        void set_center_position(const math::Vector &position);
        
    protected:
        double angle_;
        math::Vector center_position_;

    private:
        void ValidateMatrix(const math::Matrix &matrix);
    };
}