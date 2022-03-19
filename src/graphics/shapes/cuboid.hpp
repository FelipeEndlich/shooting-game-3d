#pragma once

#include "./model_3d.hpp"

namespace graphics::shapes
{
    class Cuboid : public Model3D
    {
    public:
        Cuboid();
        Cuboid(const math::Vector &origin, double width, double height);
        Cuboid(const math::Vector &origin, double width, double height, const graphics::color::RGBA &color);
        Cuboid(const Cuboid &other);
        Cuboid(const Cuboid &&other);
        ~Cuboid() = default;

        Cuboid &operator=(const Cuboid &other);
        Cuboid &operator=(const Cuboid &&other);

        double get_width() const;
        double get_height() const;

        virtual math::Vector get_center_position() const override;

    protected:
        double width_;
        double height_;

    private:
        void BuildPoints(const math::Vector &origin, double width, double height);
    };
}