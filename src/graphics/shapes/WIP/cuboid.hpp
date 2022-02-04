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
        //Cuboid(const math::Matrix &matrix);
        //Cuboid(const math::Matrix &matrix, const graphics::color::RGBA &color);
        //Cuboid(const Cuboid &other);
        //Cuboid(const Cuboid &&other);
        virtual ~Cuboid() = default;

        math::Vector get_center_position() const override;

    private:
        float width;
        float height;
        float depth;

        void BuildPoints(double width, double height, double depth, const math::Vector &initial_position);
    };
}