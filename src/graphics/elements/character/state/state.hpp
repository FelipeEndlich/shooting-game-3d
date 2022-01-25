#pragma once

#include "../direction.hpp"
#include <string>

namespace graphics::elements::character
{
    class Character;

    class State
    {
    public:
        State();
        State(State &state)
            : character(state.character), direction(state.direction){};
        State(Character *character)
            : character(character) {}
        virtual ~State() {}

        std::string getName() const;

        virtual void fall(double deltaTime) = 0;
        virtual void jump(double deltaTime) = 0;
        virtual void stop(double deltaTime) = 0;
        virtual void move(double deltaTime, Direction direction) = 0;

        virtual State *clone() = 0;

        // to strng method
        virtual std::string toString() const;

    protected:
        Character *character;
        Direction direction = Direction::RIGHT;
        std::string name = "Unnamed";
    };
}