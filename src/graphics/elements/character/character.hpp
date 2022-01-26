#pragma once

#include "../../../physics/rigidBody.hpp"
#include "../../../math/vector.hpp"
#include "../../color/rgba.hpp"
#include "../../shapes/rectangle.hpp"
#include "../../shapes/circle.hpp"
#include "./direction.hpp"
#include "./state/state.hpp"
#include "./state/grounded_state.hpp"
#include "./state/walking_left_state.hpp"
#include "./state/walking_right_state.hpp"

namespace graphics::elements::state
{
    class Character : public physic::RigidBody
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

        void setState(BaseState *state);

    private:
        graphics::shapes::Circle shape;
        BaseState *state;

        void allocate();
        void deallocate();

        friend class GroundedState;
        friend class WalkingLeftState;
        friend class WalkingRightState;
    };
}