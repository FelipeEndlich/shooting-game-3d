#pragma once

#include "../../../physics/rigidBody.hpp"
#include "../../../math/vector.hpp"
#include "../../color/rgba.hpp"
#include "../../shapes/rectangle.hpp"
#include "../../shapes/circle.hpp"
#include "./direction.hpp"
#include "./state/state.hpp"
#include "./state/groundedState.hpp"
#include "./state/walkingLeftState.hpp"
#include "./state/walkingRightState.hpp"

namespace graphics::elements::character
{
    class Character : public physics::RigidBody
    {

    public:
        Character();
        Character(math::Vector &initialPosition, double radius, graphics::color::RGBA &color);
        ~Character();

        Character &operator=(const Character &other);

        void render();

        void fall(double deltaTime);
        void jump(double deltaTime);
        void stop(double deltaTime);
        void move(double deltaTime, Direction direction);

        void setState(State *state);

    private:
        graphics::shapes::Circle shape;
        State *state;

        void allocate();
        void deallocate();

        friend class GroundedState;
        friend class WalkingLeftState;
        friend class WalkingRightState;
    };
}