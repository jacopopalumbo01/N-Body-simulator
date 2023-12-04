#ifndef BOUNDARY
#define BOUNDARY

#include "../Particle/Particle.hpp"

namespace NBodyEnv {
class Boundary {
public:
  Boundary() = default;
  virtual void checkDomain(Particle &particle);
  ~Boundary() = default;
};
} // namespace NBodyEnv

#endif
