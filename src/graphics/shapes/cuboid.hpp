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
        double get_depth() const;

        void Draw() override;

        virtual math::Vector get_center_position() const override;

    protected:
        double width_;
        double height_;
        double depth_;

    private:
        void __draw_interface();
        void __draw_face(double z);
        void __draw_line(double xi, double yi, double zi, double xf, double yf, double zf);
        void __draw_quad_face(math::Vector p1, math::Vector p2, math::Vector p3, math::Vector p4);
        void BuildPoints(const math::Vector &origin, double width, double height, double depth);
    };
}