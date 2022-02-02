#pragma once

#include "base_state.hpp"

#include "../../../../physics/direction.hpp"
#include "../../../../physics/icollidable.hpp"
#include "../../../../math/vector.hpp"

namespace graphics::elements::character
{
    class Character;

    class JumpingRightState : public BaseState
    {
    public:
        JumpingRightState(JumpingRightState &state);
        JumpingRightState(Character *character);
        ~JumpingRightState() {}

        virtual BaseState *Clone() override;
        virtual void Jump(double delta_time) override;
        virtual void Jump(double delta_time, physic::Direction direction) override;
        virtual void Stop(double delta_time) override;
        virtual void Move(double delta_time, physic::Direction direction) override;
        virtual void ProcessCollision(physic::ICollidable *collidable) override;
    };
}
