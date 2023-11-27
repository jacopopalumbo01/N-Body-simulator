#ifndef FUNCTIONS
#define FUNCTIONS

#include "../Particle/Particle.hpp"
#include <functional>

namespace NBodyEnv {
constexpr double G = 6.67408e-11;
class Functions {
public:
  // The gravitational function
  static void getGrav(Particle &p1, Particle &p2);
  static std::function<void(Particle &, Particle &)> getGravFunc() {
    return getGrav;
  }
};
} // namespace NBodyEnv

#endif
