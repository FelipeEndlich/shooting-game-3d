#pragma once

#include "base_state.hpp"

#include "../../../../physics/direction.hpp"
#include "../../../../physics/icollidable.hpp"
#include "walk_phase.hpp"

namespace graphics::elements::character
{
    class Character;

    class WalkingLeftState : public BaseState
    {
    public:
        WalkingLeftState(WalkingLeftState &state);
        WalkingLeftState(Character *character);
        ~WalkingLeftState() {}

        virtual BaseState *Clone() override;
        virtual void Jump(double delta_time, physic::Direction direction) override;
        virtual void Stop(double delta_time) override;
        virtual void Move(double delta_time, physic::Direction direction) override;
        virtual void ProcessCollision(physic::ICollidable *collidable) override;
        virtual void ProcessGravity() override;

    private:
        WalkPhase phase_;
        bool right_front_leg_ = true;

        void Animate();
    };
}
