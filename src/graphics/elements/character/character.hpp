#pragma once

#include "../../../physics/rigidBody.hpp"
#include "../../../math/vector.hpp"
#include "../../color/rgba.hpp"
#include "../../shapes/rectangle.hpp"
#include "../../shapes/circle.hpp"

using namespace math;
using namespace physics;
using namespace graphics::shapes;
using namespace graphics::color;

namespace graphics
{
    namespace elements
    {
        namespace character
        {
            class Character : public RigidBody
            {
            public:
                Character();
                Character(Vector &initialPosition, double radius, RGBA &color);

                void render();

            private:
                Circle shape;
            };
        }
    }
}