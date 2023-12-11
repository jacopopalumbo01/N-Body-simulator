#include "../../inc/Collisions/CubeBoundary.hpp"

namespace NBodyEnv {
void CubeBoundary::checkDomain(Particle &particle) {
  // Check on X planes: we have collision with x plane if x coord of the
  // particle is greater equal/less equal of both x planes.
  if ((particle.getPos().xPos >= planes[0] &&
       particle.getPos().xPos >= planes[1]) ||
      (particle.getPos().xPos <= planes[0] &&
       particle.getPos().xPos <= planes[1]))
    particle.invertX();

  // Check on Y planes
  if ((particle.getPos().yPos >= planes[2] &&
       particle.getPos().yPos >= planes[3]) ||
      (particle.getPos().yPos <= planes[2] &&
       particle.getPos().yPos <= planes[3]))
    particle.invertY();

  // Check on Z planes
  if ((particle.getPos().zPos >= planes[4] &&
       particle.getPos().zPos >= planes[5]) ||
      (particle.getPos().zPos <= planes[4] &&
       particle.getPos().zPos <= planes[5]))
    particle.invertZ();
}
} // namespace NBodyEnv
