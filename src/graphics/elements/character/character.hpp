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
#include "./state/falling_state.hpp"
#include "./state/falling_left_state.hpp"
#include "./state/falling_right_state.hpp"
#include "./state/jumping_state.hpp"
#include "./state/jumping_right_state.hpp"
#include "./state/jumping_left_state.hpp"

namespace graphics::elements::state
{
    class Character : public physic::RigidBody, public physic::ICollidable
    {

    public:
        Character(bool collision_processable = true);
        Character(math::Vector &initial_position, double radius, graphics::color::RGBA &color, bool collision_processable = true);
        ~Character();

        Character &operator=(const Character &other);

        void Render();

        void Jump(double delta_time);
        void Jump(double delta_time, physic::Direction direction);
        void Stop(double delta_time);
        void Move(double delta_time, physic::Direction direction);

        void set_state(BaseState *state);

        math::Vector get_position() override;
        double get_width() override;
        double get_height() override;
        void ProcessCollision(ICollidable *collidable) override;

        inline static double default_horizontal_velocity_ = 0.1;

    private:
        graphics::shapes::Circle shape_;
        BaseState *state_;
        math::Vector initial_jump_velocity_;
        bool collision_processable_;

        void ProcessMove(double delta_time);

        void Allocate();
        void Deallocate();

        friend class FallingState;
        friend class FallingLeftState;
        friend class FallingRightState;
        friend class GroundedState;
        friend class JumpingState;
        friend class JumpingLeftState;
        friend class JumpingRightState;
        friend class WalkingLeftState;
        friend class WalkingRightState;
    };
}