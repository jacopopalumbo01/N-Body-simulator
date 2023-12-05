#ifndef CUBEBOUNDARY
#define CUBEBOUNDARY

#include "../Particle/Particle.hpp"
#include "Boundary.hpp"

namespace NBodyEnv {
class CubeBoundary : virtual Boundary {
public:
  CubeBoundary() = default;
  void checkDomain(Particle &particle);
  ~CubeBoundary() = default;

private:
  double x, y, z;
};
} // namespace NBodyEnv

#endif
