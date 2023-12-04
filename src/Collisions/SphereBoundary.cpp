#include "../../inc/Collisions/SphereBoundary.hpp"

namespace NBodyEnv {
void SphereBoundary::checkDomain(Particle &particle) {
  // Compare center - particle distance and sphere radius
  if (_center.getDistance(particle.getPos()) >= _radius) {
    // Collision -> TODO manage collision on particle
  }
}
} // namespace NBodyEnv
