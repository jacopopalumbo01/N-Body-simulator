#ifndef FUNCTIONS
#define FUNCTIONS

#include "../Particle/Particle.hpp"

namespace NBodyEnv {
constexpr double G = 6.67408e-11;
class Functions {
public:
  // The gravitational function
  static void getGrav(Particle &p1, Particle &p2);
};
} // namespace NBodyEnv

#endif
