#pragma once

#include "state.hpp"

namespace graphics::elements::state
{
    class Character;

    class WalkingLeftState : public BaseState
    {
    public:
        WalkingLeftState(WalkingLeftState &state);
        WalkingLeftState(Character *character);
        ~WalkingLeftState() {}

        virtual BaseState *Clone() override;
        virtual void Fall(double delta_time) override;
        virtual void Jump(double delta_time) override;
        virtual void Stop(double delta_time) override;
        virtual void Move(double delta_time, Direction direction) override;
    };
}
