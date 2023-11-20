#include "GravParticle.hpp"
#include <cmath>

namespace NBodyEnv
{

    // define gloabl variable gravitational constant
    constexpr double G = 6.67408e-11;
    // Static member to store a dummy force
    static Force dummyForce{0.0, 0.0, 0.0};

    const Force &GravParticle::computeForce(const Particle &p2) const
    {
        // no need to dynamically cast p2 to gravParticle, can always convert generic particle to gravParticle with implicit downcasting 
        // compute the distance between the two particles in 3D
        double xDistance = getPos().xPos - p2.getPos().xPos;
        double yDistance = getPos().yPos - p2.getPos().yPos;
        double zDistance = getPos().zPos - p2.getPos().zPos;
        double distance = sqrt(xDistance * xDistance + yDistance * yDistance + zDistance * zDistance);

        double totMass = getSpecInfo() * p2.getSpecInfo();
        // compute contributes along each axis
        // could have also used pow(distance, 3) instead of distanceCubed, but needs compiler flag -ffast-math to be efficient as naive method
        // need to actually understand if using more memory is worth it, so that we avoid computing again distanceCubed and totMass
        double distanceCubed = distance * distance * distance;
        dummyForce.xForce = (-G * totMass / distanceCubed )* xDistance;
        dummyForce.yForce = (-G * totMass / distanceCubed) * yDistance;
        dummyForce.zForce = (-G * totMass / distanceCubed) * zDistance;

        // TODO: evaluate possibility of updating the force of the patricles inside the body of the function
        // in this case the method and the object passed as parameter are not constant, moreover it returns a void

        return dummyForce;
    }

}; // namespace NBodyEnv
