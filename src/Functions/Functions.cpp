#include "Functions/Functions.hpp"
#include "Collisions/Collisions.hpp"
#include <iostream>
#include <math.h>
#include <iostream>

namespace NBodyEnv
{
  void Functions::getGrav(Particle &p1, Particle &p2)
  {

    // Dummy force
    Force dummyForce{0.0, 0.0, 0.0};

    // compute the distance between p1 and p2 in parallel
    double xDistance = p1.getPos().xPos - p2.getPos().xPos;
    double yDistance = p1.getPos().yPos - p2.getPos().yPos;
    double zDistance = p1.getPos().zPos - p2.getPos().zPos;
    double distance = sqrt(xDistance * xDistance + yDistance * yDistance +
                           zDistance * zDistance);

    // Detect collision between the two particles
    if (distance <= p1.getRadius() + p2.getRadius())
    {
      // two particles have collided, compute perfectly inelastic collision which results in the merging of the two particles
      // NBodyEnv::Collisions::getInelasticCollision()(p1, p2);
      return;
    }

    // Calculate mass product
    double totMass = p1.getSpecInfo() * p2.getSpecInfo();

    // Compute contributes along each axis in parallel for each component
    double distanceCubed = distance * distance * distance;

    dummyForce.xForce = (-G * totMass / distanceCubed) * xDistance;
    dummyForce.yForce = (-G * totMass / distanceCubed) * yDistance;
    dummyForce.zForce = (-G * totMass / distanceCubed) * zDistance;

    // add force contributions to both particles, invert it for the second one
    p1.addForce(dummyForce);
  }

  void Functions::getGravSerial(Particle &p1, Particle &p2)
  {

    // Dummy force
    Force dummyForce{0.0, 0.0, 0.0};

    // compute the distance between p1 and p2 in parallel
    double xDistance = p1.getPos().xPos - p2.getPos().xPos;
    double yDistance = p1.getPos().yPos - p2.getPos().yPos;
    double zDistance = p1.getPos().zPos - p2.getPos().zPos;
    double distance = sqrt(xDistance * xDistance + yDistance * yDistance +
                           zDistance * zDistance);

    // Detect collision between the two particles
    if (distance <= p1.getRadius() + p2.getRadius())
    {
      // two particles have collided, compute perfectly inelastic collision which results in the merging of the two particles
      // NBodyEnv::Collisions::getInelasticCollision()(p1, p2);
      return;
    }

    // Calculate mass product
    double totMass = p1.getSpecInfo() * p2.getSpecInfo();

    // Compute contributes along each axis in parallel for each component
    double distanceCubed = distance * distance * distance;

    dummyForce.xForce = (-G * totMass / distanceCubed) * xDistance;
    dummyForce.yForce = (-G * totMass / distanceCubed) * yDistance;
    dummyForce.zForce = (-G * totMass / distanceCubed) * zDistance;

    // add force contributions to both particles, invert it for the second one
    p1.addForce(dummyForce);
    dummyForce.invert();
    dummyForce.xForce = -dummyForce.xForce;
    dummyForce.yForce = -dummyForce.yForce;
    dummyForce.zForce = -dummyForce.zForce;
    p2.addForce(dummyForce);
  }

  Force Functions::getGravTwo(Pos &p1, Pos &p2, double mOne, double mTwo, double radOne, double radTwo)
  {

    // Dummy force
    Force dummyForce{0.0, 0.0, 0.0};

    // compute the distance between p1 and p2 in parallel
    double xDistance = p1.xPos - p2.xPos;
    double yDistance = p1.yPos - p2.yPos;
    double zDistance = p1.zPos - p2.zPos;
    double distance = sqrt(xDistance * xDistance + yDistance * yDistance +
                           zDistance * zDistance);

    // Calculate mass product
    double totMass = mOne * mTwo;

    // Compute contributes along each axis in parallel for each component
    double distanceCubed = distance * distance * distance;

    dummyForce.xForce = (-G * totMass / distanceCubed) * xDistance;
    dummyForce.yForce = (-G * totMass / distanceCubed) * yDistance;
    dummyForce.zForce = (-G * totMass / distanceCubed) * zDistance;

    // Detect collision between the two particles
    if (distance <= radOne + radTwo)
    {
      // two particles have collided, compute perfectly inelastic collision which results in the merging of the two particles
      // NBodyEnv::Collisions::getInelasticCollision()(p1, p2);
      dummyForce.xForce = 0.0;
      dummyForce.yForce = 0.0;
      dummyForce.zForce = 0.0;
      return dummyForce;
    }

    return dummyForce;
  }

} // namespace NBodyEnv
