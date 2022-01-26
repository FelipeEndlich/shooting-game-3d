#pragma once

#include "base_state.hpp"

#include "../../../../physics/direction.hpp"

namespace graphics::elements::state
{
    class Character;

    class WalkingRightState : public BaseState
    {
    public:
        WalkingRightState(WalkingRightState &state);
        WalkingRightState(Character *character);
        ~WalkingRightState() {}

        virtual BaseState *Clone() override;
        virtual void Fall(double delta_time) override;
        virtual void Jump(double delta_time) override;
        virtual void Stop(double delta_time) override;
        virtual void Move(double delta_time, physic::Direction direction) override;
    };
}
