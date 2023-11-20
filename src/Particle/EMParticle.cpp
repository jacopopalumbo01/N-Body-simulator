#include "EMParticle.hpp"

namespace NBodyEnv
{
    // Static member to store a dummy force
    static const Force dummyForce{0.0, 0.0, 0.0};

    // method to compute the electromagnetic force between two particles
    const Force &EMParticle::computeForce(const Particle &p2) const
    {
        // TODO: implement this

        return dummyForce;
    }

}; // namespace NBodyEnv