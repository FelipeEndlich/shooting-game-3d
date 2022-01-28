#pragma once

#include <vector>

#include "icollidable.hpp"

namespace physic
{
    class GravityConstraintSystem
    {
    public:
        void AddSurface(ICollidable *surface);
        void RemoveSurface(ICollidable *surface);

        void AddCorp(ICollidable *corp);
        void RemoveCorp(ICollidable *corp);

        void ProcessGravityEffects();

    private:
        std::vector<ICollidable *> surfaces_;
        std::vector<ICollidable *> corps_;
    };
}