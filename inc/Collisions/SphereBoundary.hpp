#ifndef SPHEREBOUNDARY
#define SPHEREBOUNDARY

#include "../Particle/Particle.hpp"
#include "Boundary.hpp"

namespace NBodyEnv {
class SphereBoundary : virtual Boundary {
public:
  SphereBoundary(Pos center, double radius)
      : _center(center), _radius(radius) {}
  void checkDomain(Particle &particle);
  ~SphereBoundary() = default;

private:
  Pos _center;
  double _radius;
};
} // namespace NBodyEnv

#endif
