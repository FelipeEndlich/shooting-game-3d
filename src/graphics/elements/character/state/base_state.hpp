#pragma once

#include <string>

#include "../../../../physics/direction.hpp"

namespace graphics::elements::state
{
    class Character;

    class BaseState
    {
    public:
        BaseState();
        BaseState(BaseState &state)
            : character_(state.character_), direction_(state.direction_){};
        BaseState(Character *character)
            : character_(character) {}
        virtual ~BaseState() {}

        std::string get_name() const;

        virtual void Fall(double delta_time) = 0;
        virtual void Jump(double delta_time) = 0;
        virtual void Stop(double delta_time) = 0;
        virtual void Move(double delta_time, physic::Direction direction) = 0;

        virtual BaseState *Clone() = 0;

        virtual std::string to_string() const;

    protected:
        Character *character_;
        physic::Direction direction_ = physic::Direction::kRight;
        std::string name_ = "Unnamed";
    };
}