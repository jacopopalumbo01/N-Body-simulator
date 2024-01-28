#ifndef CUBEBOUNDARY
#define CUBEBOUNDARY

#include "Particle/Particle.hpp"
#include "Boundary.hpp"
#include <vector>

namespace NBodyEnv
{
  class CubeBoundary : virtual Boundary
  {
  public:
    CubeBoundary(std::array<double,6> planes) : planes(planes) {}
    void checkDomain(Particle &particle);
    Pos getOutsidePos();
    ~CubeBoundary() = default;

  private:
    std::array<double,6> planes;
  };
} // namespace NBodyEnv

#endif
