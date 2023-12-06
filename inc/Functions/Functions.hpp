#ifndef FUNCTIONS
#define FUNCTIONS

#include "../Particle/Particle.hpp"
#include "../Particle/ParticleVerlet.hpp"
#include <functional>

namespace NBodyEnv
{
  constexpr double G = 6.67408e-11;
  class Functions
  {
  public:
    // The gravitational function
    static void getGrav(Particle &p1, Particle &p2);
    static std::function<void(Particle &, Particle &)> getGravFunc()
    {
      return getGrav;
    }
    static void getGravVerlet(ParticleVerlet &p1, ParticleVerlet &p2);
    static std::function<void(ParticleVerlet &, ParticleVerlet &)> getGravFuncVerlet() {
    return getGravVerlet;
  }
  };
} // namespace NBodyEnv

#endif
