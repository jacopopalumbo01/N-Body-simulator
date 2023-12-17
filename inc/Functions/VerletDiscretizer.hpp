#ifndef VERLETDISCRETIZER
#define VERLETDISCRETIZER

#include "../Particle/Particle.hpp"
#include <functional>
#include <vector>

namespace NBodyEnv
{
  class VerletDiscretizer
  {
  public:
    static void discretize(Particle &p, Particle &prevP, double deltaTime, std::vector<Particle> &system);
    static std::function<void(Particle &, Particle &, double deltaTime, std::vector<Particle> &)> getDiscretizer(){return discretize;};
    static void updatePos(Particle &p, Particle &prevP, double deltaTime);
    static void updateFirsePos(Particle &p, double deltaTime);
  };
} // namespace NBodyEnv

#endif
