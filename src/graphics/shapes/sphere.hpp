#pragma once

#include "model_3d.hpp"
#include "../color/rgba.hpp"
#include "../../math/vector.hpp"

namespace graphics::shapes
{
    class Sphere : public Model3D
    {
    public:
        Sphere(double radius);
        Sphere(double radius, const math::Vector &initial_position);
        Sphere(double radius, const math::Vector &initial_position, const color::RGBA &color);
        virtual ~Sphere() = default;

        math::Vector get_center_position() const override;
        virtual void Draw() override;

    private:
        double radius_;
        int sector_ = 10;
        int stacks_ = 20;

        void BuildPoints(const math::Vector &initial_position);
    };
}