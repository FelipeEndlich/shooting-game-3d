#pragma once

#include <vector>

#include "icollidable.hpp"
#include "igravity_affectable.hpp"

namespace physic
{
    class GravityConstraintSystem
    {
    public:
        void AddSurface(ICollidable *surface);
        void RemoveSurface(ICollidable *surface);

        void AddCorp(IGravityAffectable *corp);
        void RemoveCorp(IGravityAffectable *corp);

        void ProcessGravityEffects();

    private:
        std::vector<ICollidable *> surfaces_;
        std::vector<IGravityAffectable *> corps_;
    };
}