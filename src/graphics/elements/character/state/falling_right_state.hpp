#pragma once

#include "base_state.hpp"

#include "../../../../physics/direction.hpp"
#include "../../../../physics/icollidable.hpp"

namespace graphics::elements::state
{
    class Character;

    class FallingRightState : public BaseState
    {
    public:
        FallingRightState(FallingRightState &state);
        FallingRightState(Character *character);
        ~FallingRightState() {}

        virtual BaseState *Clone() override;
        virtual void Jump(double delta_time) override;
        virtual void Jump(double delta_time, physic::Direction direction) override;
        virtual void Stop(double delta_time) override;
        virtual void Move(double delta_time, physic::Direction direction) override;
        virtual void ProcessCollision(physic::ICollidable *collidable) override;
    };
}
