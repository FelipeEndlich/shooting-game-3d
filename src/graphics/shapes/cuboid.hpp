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
        Cuboid(double width, double height, double depth, const math::Vector &initial_position);
        virtual ~Cuboid() = default;

        math::Vector get_center_position() const override;
        virtual void Draw() override;
        void DrawLines();

    private:
        double width;
        double height;
        double depth;
        math::Vector initial_position;

        void __draw_interface();
        void __draw_face(double z);
        void __draw_line(double xi, double yi, double zi, double xf, double yf, double zf);
        void __draw_quad_face(math::Vector p1, math::Vector p2, math::Vector p3, math::Vector p4);
        void BuildPoints();
    };
}