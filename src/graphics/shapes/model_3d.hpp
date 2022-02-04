#pragma once

#include "./model.hpp"
#include "./../color/rgba.hpp"
#include "./../../math/matrix.hpp"
#include "./../../math/vector.hpp"

namespace graphics::shapes
{
    class Model3D : public Model
    {
    public:
        Model3D();
        Model3D(const math::Matrix &matrix);
        Model3D(const math::Matrix &matrix, const graphics::color::RGBA &color);
        Model3D(const Model3D &other);
        Model3D(const Model3D &&other);
        virtual ~Model3D() = default;

        virtual void Translate(double dx, double dy, double dz);
        virtual void Translate(const math::Vector &vector) override;

        virtual void Scale(double x, double y, double z, double sx, double sy, double sz);
        virtual void Scale(const math::Vector &center, double sx, double sy, double sz);
        virtual void Scale(double x, double y, double z, const math::Vector &scale_vector);
        virtual void Scale(const math::Vector &center, const math::Vector &scale_vector) override;

        virtual void Rotate(double x, double y, double z, double phi, double psi, double theta);
        virtual void Rotate(double x, double y, double z, math::Vector &radians);
        virtual void Rotate(const math::Vector &center, double phi, double psi, double theta);
        virtual void Rotate(const math::Vector &center, const math::Vector &radians) override;

        virtual void Transform(const math::Matrix &matrix) override;
        virtual void Transform(double x, double y, double z, double sx, double sy, double sz, double phi, double psi, double theta);
        virtual void Transform(const math::Vector &center, double sx, double sy, double sz, double phi, double psi, double theta);
        virtual void Transform(double x, double y, double z, const math::Vector &scale, double phi, double psi, double theta);
        virtual void Transform(double x, double y, double z, double sx, double sy, double sz, const math::Vector &radians);
        virtual void Transform(const math::Vector &center, const math::Vector &scale, double phi, double psi, double theta);
        virtual void Transform(const math::Vector &center, double sx, double sy, double sz, const math::Vector &radians);
        virtual void Transform(double x, double y, double z, const math::Vector &scale, const math::Vector &radians);
        virtual void Transform(const math::Vector &center, const math::Vector &scale, const math::Vector &radians) override;

        virtual void Draw();

        virtual math::Vector get_angle() const;
        virtual math::Vector get_center_position() const = 0;

    protected:
        math::Vector angle_;

    private:
        void ValidateMatrix(const math::Matrix &matrix);
    };
}