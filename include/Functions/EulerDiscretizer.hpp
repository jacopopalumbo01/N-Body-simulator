#ifndef EULERDISCRETIZER
#define EULERDISCRETIZER

#include "Particle/Particle.hpp"
#include <functional>

namespace NBodyEnv
{
  class EulerDiscretizer
  {
  public:
    static void discretize(Particle &p1, double deltaTime);
    static std::function<void(Particle &, double deltaTime)> getDiscretizer()
    {
      return discretize;
    }
  };
} // namespace NBodyEnv

#endif
