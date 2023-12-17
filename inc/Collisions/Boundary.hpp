#ifndef BOUNDARY
#define BOUNDARY

#include "../Particle/Particle.hpp"

namespace NBodyEnv
{
  class Boundary
  {
  public:
    Boundary() = default;
    // method to check if particle is inside the domain
    virtual void checkDomain(Particle &particle);
    // method to return a position outside the domain, used to teleport particles that have been absorbed
    // without the need to actually removing them from the system (which is problematic for the graphic simulation)
    virtual Pos getOutsidePos();
    ~Boundary() = default;
  };
} // namespace NBodyEnv

#endif
