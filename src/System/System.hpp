#ifndef SYSTEM
#define SYSTEM

#include "../Particle/Particle.hpp"
#include <iostream>
#include <vector>

namespace NBodyEnv {
class System {
public:
  System(){};
  ~System() = default;
  void compute();
  void addParticle(Particle particle);
  const Particle &getParticle(int index) const;

private:
  std::vector<NBodyEnv::Particle> _systemParticles;
};
} // namespace NBodyEnv

#endif
