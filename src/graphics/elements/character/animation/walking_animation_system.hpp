#pragma once

#include "walk_phase.hpp"

#include <map>
#include <tuple>

namespace graphics::elements::character
{
    class Character;

    class WalkingAnimationSystem
    {
    public:
        WalkingAnimationSystem() = default;
        WalkingAnimationSystem(Character *character);

        void Animate();

    private:
        Character *character_;
        WalkPhase phase_;
        std::map<std::string, std::map<WalkPhase, std::tuple<double, double>>> phase_info_;
        bool right_front_leg_ = true;

        bool IsDoubleEq(double a, double b, double epsilon);
        double CalculateIncrement(std::tuple<double, double> angles);
    };
}