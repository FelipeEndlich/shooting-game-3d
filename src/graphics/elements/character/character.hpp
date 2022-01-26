#pragma once

#include "../../../physics/rigid_body.hpp"
#include "../../../physics/direction.hpp"
#include "../../../physics/icollidable.hpp"
#include "../../../math/vector.hpp"
#include "../../color/rgba.hpp"
#include "../../shapes/rectangle.hpp"
#include "../../shapes/circle.hpp"
#include "./state/base_state.hpp"
#include "./state/grounded_state.hpp"
#include "./state/walking_left_state.hpp"
#include "./state/walking_right_state.hpp"

namespace graphics::elements::state
{
    class Character : public physic::RigidBody, public physic::ICollidable
    {

    public:
        Character();
        Character(math::Vector &initial_position, double radius, graphics::color::RGBA &color);
        ~Character();

        Character &operator=(const Character &other);

        void Render();

        void Fall(double delta_time);
        void Jump(double delta_time);
        void Stop(double delta_time);
        void Move(double delta_time, physic::Direction direction);

        void set_state(BaseState *state);

        math::Vector get_position() override;
        double get_width() override;
        double get_height() override;
        void ProcessCollision(ICollidable *collidable) override;

    private:
        graphics::shapes::Circle shape_;
        BaseState *state_;

        void Allocate();
        void Deallocate();

        friend class GroundedState;
        friend class WalkingLeftState;
        friend class WalkingRightState;
    };
}