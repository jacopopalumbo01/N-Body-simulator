#include "Functions/Functions.hpp"
#include "Collisions/Collisions.hpp"
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

    // compute the distance between p1 and p2 in parallel
    double xDistance, yDistance, zDistance;
#if defined(_OPENMP)
#pragma omp parallel sections
#endif
    {
#if defined(_OPENMP)
#pragma omp section
#endif
      {
        xDistance = p1.getPos().xPos - p2.getPos().xPos;
      }
#if defined(_OPENMP)
#pragma omp section
#endif
      {
        yDistance = p1.getPos().yPos - p2.getPos().yPos;
      }
#if defined(_OPENMP)
#pragma omp section
#endif
      {
        zDistance = p1.getPos().zPos - p2.getPos().zPos;
      }
    }

    // double yDistance = p1.getPos().yPos - p2.getPos().yPos;
    // double zDistance = p1.getPos().zPos - p2.getPos().zPos;
    double distance = sqrt(xDistance * xDistance + yDistance * yDistance +
                           zDistance * zDistance);

    // Detect collision between the two particles
    if (distance <= p1.getRadius() + p2.getRadius())
    {
      // two particles have collided, compute perfectly inelastic collision which results in the merging of the two particles
      // NBodyEnv::Collisions::getElasticCollision()(p1, p2);
      return;
    }

    // Calculate mass product
    double totMass = p1.getSpecInfo() * p2.getSpecInfo();

    // Compute contributes along each axis in parallel for each component
    double distanceCubed = distance * distance * distance;
#if defined(_OPENMP)
#pragma omp parallel sections
#endif
    {
#if defined(_OPENMP)
#pragma omp section
#endif
      {
        dummyForce.xForce = (-G * totMass / distanceCubed) * xDistance;
      }
#if defined(_OPENMP)
#pragma omp section
#endif
      {
        dummyForce.yForce = (-G * totMass / distanceCubed) * yDistance;
      }
#if defined(_OPENMP)
#pragma omp section
#endif
      {
        dummyForce.zForce = (-G * totMass / distanceCubed) * zDistance;
      }
    }

    // dummyForce.xForce = (-G * totMass / distanceCubed) * xDistance;
    // dummyForce.yForce = (-G * totMass / distanceCubed) * yDistance;
    // dummyForce.zForce = (-G * totMass / distanceCubed) * zDistance;

    // add force contributions to both particles, invert it for the second one
    p1.addForce(dummyForce);
    dummyForce.invert();
    p2.addForce(dummyForce);
  }

} // namespace NBodyEnv
