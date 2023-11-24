#include "Functions.hpp"
#include <math.h>

namespace NBodyEnv {
void Functions::getGrav(Particle &p1, Particle &p2) {
  // Dummy force
  Force dummyForce{0.0, 0.0, 0.0};

  // Calculate distance between p1 and p2
  double xDistance = p1.getPos().xPos - p2.getPos().xPos;
  double yDistance = p1.getPos().yPos - p2.getPos().yPos;
  double zDistance = p1.getPos().zPos - p2.getPos().zPos;
  double distance = sqrt(xDistance * xDistance + yDistance * yDistance +
                         zDistance * zDistance);

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
