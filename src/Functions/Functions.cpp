#include "../../inc/Functions/Functions.hpp"
#include "../../inc/Collisions/Collisions.hpp"
#include <iostream>
#include <math.h>
#include <iostream>
#include <omp.h>

namespace NBodyEnv
{
  void Functions::getGrav(Particle &p1, Particle &p2)
  {

    // Dummy force
    Force dummyForce{0.0, 0.0, 0.0};

    if (p2.getVisible() == false)
    {
      // p2 is invisible, it has previously collided with another particle ==> don't compute the force between the two
      // since this particle should no longer be considered
      return;
    }

    // Calculate distance between p1 and p2
    double xDistance = p1.getPos().xPos - p2.getPos().xPos;
    double yDistance = p1.getPos().yPos - p2.getPos().yPos;
    double zDistance = p1.getPos().zPos - p2.getPos().zPos;
    double distance = sqrt(xDistance * xDistance + yDistance * yDistance +
                           zDistance * zDistance);

    // Detect collision
    if (distance <= p1.getRadius() + p2.getRadius())
    {
      // two particles have collided, compute perfectly inelastic collision which results in the merging of the two particles
      // NBodyEnv::Collisions::getInelasticCollision()(p1, p2);
      return;
    }

    // Calculate mass product
    double totMass = p1.getSpecInfo() * p2.getSpecInfo();

    // Compute contributes along each axis
    double distanceCubed = distance * distance * distance;
    dummyForce.xForce = (-G * totMass / distanceCubed) * xDistance;
    dummyForce.yForce = (-G * totMass / distanceCubed) * yDistance;
    dummyForce.zForce = (-G * totMass / distanceCubed) * zDistance;

    // add force contributions to both particles, invert it for the second one
    p1.addForce(dummyForce);
    dummyForce.invert();
    p2.addForce(dummyForce);
  }

  // TODO: insert inelastic collision check as done in the method above, same for computeVerlet() method
  void Functions::getGravVerlet(ParticleVerlet &p1, ParticleVerlet &p2)
  {

    // Dummy force
    Force dummyForce{0.0, 0.0, 0.0};

    // Calculate distance between p1 and p2
    double xDistance = p1.getPos().xPos - p2.getPos().xPos;
    double yDistance = p1.getPos().yPos - p2.getPos().yPos;
    double zDistance = p1.getPos().zPos - p2.getPos().zPos;
    double distance = sqrt(xDistance * xDistance + yDistance * yDistance +
                           zDistance * zDistance);

    // Detect collision
    if (distance <= p1.getRadius() + p2.getRadius())
    {
      return;
    }

    // Calculate mass product
    double totMass = p1.getSpecInfo() * p2.getSpecInfo();

    // Compute contributes along each axis
    double distanceCubed = distance * distance * distance;
    dummyForce.xForce = (-G * totMass / distanceCubed) * xDistance;
    dummyForce.yForce = (-G * totMass / distanceCubed) * yDistance;
    dummyForce.zForce = (-G * totMass / distanceCubed) * zDistance;

    // Modify particles
    p1.addForce(dummyForce);
    dummyForce.invert();
    p2.addForce(dummyForce);
  }
} // namespace NBodyEnv
