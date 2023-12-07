#include "../../inc/Functions/Functions.hpp"
#include "../../inc/Collisions/Collisions.hpp"
#include <iostream>
#include <math.h>
#include <iostream>
#include <omp.h>

namespace NBodyEnv {
void Functions::getGrav(Particle &p1, Particle &p2) {

  // Dummy force
  Force dummyForce{0.0, 0.0, 0.0};

  if(p2.getVisible() == false) 
  {
    // p2 is invisible ==> don't compute the force between the two
    // don't do any computation, since the force is zero and the velocity should stay constant
    return;
  }

  // Calculate distance between p1 and p2
  double xDistance = p1.getPos().xPos - p2.getPos().xPos;
  double yDistance = p1.getPos().yPos - p2.getPos().yPos;
  double zDistance = p1.getPos().zPos - p2.getPos().zPos;
  double distance = sqrt(xDistance * xDistance + yDistance * yDistance +
                         zDistance * zDistance);

  // Detect collision
  if (distance <= p1.getRadius() + p2.getRadius()) {
    NBodyEnv::Collisions::getInelasticCollision()(p1, p2);
    return;
  }

  // check for boundary conditions
  // if a particle goes out of the domain, it will simulate an elastic collision
  // ==> just need to invert the velocity component along the axis where the
  // particle has gone out of the domain
  // TODO: move this somewhere else, since the new velocity values are gonna be
  // overwritten by the System::compute() function when it calls
  // iter->updateVel(_deltaTime) if(p1.getPos().xPos > 1.0 || p1.getPos().xPos <
  // -1.0)
  // {
  //   p1.setVel({-p1.getVel().xVel, p1.getVel().yVel, p1.getVel().zVel});
  // }
  // else if (p1.getPos().yPos > 1.0 || p1.getPos().yPos < -1.0)
  // {
  //   p1.setVel({p1.getVel().xVel, -p1.getVel().yVel, p1.getVel().zVel});
  // }
  // else if (p1.getPos().zPos > 1.0 || p1.getPos().zPos < -1.0)
  // {
  //   p1.setVel({p1.getVel().xVel, p1.getVel().yVel, -p1.getVel().zVel});
  // }

  // // same for p2
  // if(p2.getPos().xPos > 1.0 || p2.getPos().xPos < -1.0)
  // {
  //   p2.setVel({-p2.getVel().xVel, p2.getVel().yVel, p2.getVel().zVel});
  // }
  // else if (p2.getPos().yPos > 1.0 || p2.getPos().yPos < -1.0)
  // {
  //   p2.setVel({p2.getVel().xVel, -p2.getVel().yVel, p2.getVel().zVel});
  // }
  // else if (p2.getPos().zPos > 1.0 || p2.getPos().zPos < -1.0)
  // {
  //   p2.setVel({p2.getVel().xVel, p2.getVel().yVel, -p2.getVel().zVel});
  // }

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

void Functions::getGravVerlet(ParticleVerlet &p1, ParticleVerlet &p2) {

  // Dummy force
  Force dummyForce{0.0, 0.0, 0.0};

  // Calculate distance between p1 and p2
  double xDistance = p1.getPos().xPos - p2.getPos().xPos;
  double yDistance = p1.getPos().yPos - p2.getPos().yPos;
  double zDistance = p1.getPos().zPos - p2.getPos().zPos;
  double distance = sqrt(xDistance * xDistance + yDistance * yDistance +
                         zDistance * zDistance);

  // Detect collision
  if (distance <= p1.getRadius() + p2.getRadius()) {
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
