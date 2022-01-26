#pragma once

#include "../../physics/rigidBody.hpp"
#include "../../math/vector.hpp"
#include "../color/rgba.hpp"
#include "../shapes/rectangle.hpp"

using namespace math;
using namespace physic;
using namespace graphics::shapes;
using namespace graphics::color;

namespace graphics::elements
{
    class Obstacle : public RigidBody
    {
    public:
        Obstacle() = default;
        Obstacle(Vector &initialPosition, double width, double height, RGBA &color);

        void render();

    private:
        Rectangle shape;
    };
}