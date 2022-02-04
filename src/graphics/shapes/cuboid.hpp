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

    private:
        float width;
        float height;
        float depth;
        math::Vector * initial_position;

        void BuildPoints(double width, double height, double depth, const math::Vector &initial_position);
    };
}