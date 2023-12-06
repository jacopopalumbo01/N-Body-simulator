#ifndef SYSTEM
#define SYSTEM

#include "../Particle/Particle.hpp"
#include "../Particle/ParticleVerlet.hpp"
#include <functional>
#include <iostream>
#include <vector>

namespace NBodyEnv {
class System {
public:
  System(std::function<void(Particle &, Particle &)> func, double deltaTime)
      : _func(func), _deltaTime(deltaTime){};
  System(std::function<void(ParticleVerlet &, ParticleVerlet &)> funcVerlet, double deltaTime)
      : _funcVerlet(funcVerlet), _deltaTime(deltaTime){};
  ~System() = default;
  void compute();
  void computeVerlet();
  void addParticle(Particle particle);
  void addParticle(ParticleVerlet particleVerlet);
  void printParticles() const;
  void printParticlesVerlet() const;
  const Particle &getParticle(int index) const;
  const ParticleVerlet &getParticleVerlet(int index) const;
  const std::vector<Particle> &getParticles() const { return _systemParticles; }
  const std::vector<ParticleVerlet> &getParticlesVerlet() const { return _systemVerlet; }

protected:
  const std::vector<Particle> &getPrevState() const { return _prevState; }
  const std::vector<ParticleVerlet> &getPrevStateVerlet() const { return _prevStateVerlet; }
  std::vector<NBodyEnv::Particle> _prevState;
  std::vector<NBodyEnv::ParticleVerlet> _prevStateVerlet;
  std::vector<NBodyEnv::Particle> _systemParticles;
  std::vector<NBodyEnv::ParticleVerlet> _systemVerlet;
  std::function<void(Particle &, Particle &)> _func;
  std::function<void(ParticleVerlet &, ParticleVerlet &)> _funcVerlet;
  double _deltaTime;
};
} // namespace NBodyEnv

#endif
