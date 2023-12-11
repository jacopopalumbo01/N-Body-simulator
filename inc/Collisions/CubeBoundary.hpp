#ifndef CUBEBOUNDARY
#define CUBEBOUNDARY

#include "../Particle/Particle.hpp"
#include "Boundary.hpp"
#include <vector>

namespace NBodyEnv {
class CubeBoundary : virtual Boundary {
public:
  CubeBoundary(double xOne, double xTwo, double yOne, double yTwo, double zOne,
               double zTwo) {
    planes.push_back(xOne);
    planes.push_back(xTwo);
    planes.push_back(yOne);
    planes.push_back(yTwo);
    planes.push_back(zOne);
    planes.push_back(zTwo);
  }
  void checkDomain(Particle &particle);
  ~CubeBoundary() = default;

private:
  std::vector<double> planes;
};
} // namespace NBodyEnv

#endif
