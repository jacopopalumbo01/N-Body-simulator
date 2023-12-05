#ifndef PARALLEL_SYSTEM
#define PARALLEL_SYSTEM

#include "../Particle/Particle.hpp"
#include <functional>
#include <iostream>
#include <vector>

namespace NBodyEnv { 
class ParallelSystem {
public:
  ParallelSystem(std::function<void(Particle &, Particle &)> func, double deltaTime)
      : _func(func), _deltaTime(deltaTime){};
  ~ParallelSystem() = default;
  void compute();
  void addParticle(Particle particle);
  const Particle &getParticle(int index) const;
  const std::vector<Particle> &getParticles() const { return _systemParticles; }

private:
  std::vector<NBodyEnv::Particle> _systemParticles;
  std::function<void(Particle &, Particle &)> _func;
  double _deltaTime;
};
} // namespace NBodyEnv

#endif
