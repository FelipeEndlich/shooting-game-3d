#pragma once

#include "../../physics/rigidBody.hpp"
#include "../../math/vector.hpp"
#include "../color/rgba.hpp"
#include "../shapes/rectangle.hpp"

using namespace math;
using namespace physics;
using namespace graphics::shapes;
using namespace graphics::color;

namespace graphics
{
    namespace elements
    {
        class Obstacle : public RigidBody
        {
        public:
            Obstacle(Vector &initialPosition, double width, double height, RGBA &color);

            void render();

        private:
            Rectangle shape;
        };
    }
}