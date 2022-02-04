#pragma once

#include "./model.hpp"
#include "./model_3d.hpp"
#include "./../color/rgba.hpp"
#include "./../../math/matrix.hpp"
#include "./../../math/vector.hpp"

namespace graphics::shapes
{
    class Cuboid : public Model3D
    {
    public:
        Cuboid(double width, double height, double depth);
        Cuboid(double width, double height, double depth, const math::Matrix &matrix);
        //Cuboid(const math::Matrix &matrix);
        //Cuboid(const math::Matrix &matrix, const graphics::color::RGBA &color);
        //Cuboid(const Cuboid &other);
        //Cuboid(const Cuboid &&other);
        virtual ~Cuboid() = default;

        void Translate(double dx, double dy, double dz) override;
        void Translate(const math::Vector &vector) override;

        void Scale(double x, double y, double z, double sx, double sy, double sz) override;
        void Scale(const math::Vector &center, double sx, double sy, double sz) override;
        void Scale(double x, double y, double z, const math::Vector &scale_vector) override;
        void Scale(const math::Vector &center, const math::Vector &scale_vector) override;

        void Rotate(double x, double y, double z, double phi, double psi, double theta) override;
        void Rotate(double x, double y, double z, math::Vector &radians) override;
        void Rotate(const math::Vector &center, double phi, double psi, double theta) override;
        void Rotate(const math::Vector &center, math::Vector &radians) override;

        void Transform(const math::Matrix &matrix) override;
        void Transform(double x, double y, double z, double sx, double sy, double sz, double phi, double psi, double theta) override;
        void Transform(const math::Vector &center, double sx, double sy, double sz, double phi, double psi, double theta) override;
        void Transform(double x, double y, double z, const math::Vector &scale, double phi, double psi, double theta) override;
        void Transform(double x, double y, double z, double sx, double sy, double sz, const math::Vector &radians) override;
        void Transform(const math::Vector &center, const math::Vector &scale, double phi, double psi, double theta) override;
        void Transform(const math::Vector &center, double sx, double sy, double sz, const math::Vector &radians) override;
        void Transform(double x, double y, double z, const math::Vector &scale, const math::Vector &radians) override;
        void Transform(const math::Vector &center, const math::Vector &scale, const math::Vector &radians) override;

        void Draw() override;

        math::Vector get_angle() const override;
        math::Vector get_center_position() const override = 0;

    private:
        float width;
        float height;
        float depth;
    };
}