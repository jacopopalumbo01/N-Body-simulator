#ifndef SYSTEM
#define SYSTEM

#include "Particle/Particle.hpp"
#include <functional>
#include <iostream>
#include <vector>

namespace NBodyEnv {
template <class T> class System {
public:
  System(std::function<void(Particle &, Particle &)> func, T discretizer,
         double deltaTime)
      : _func(func), _discretizer(discretizer), _deltaTime(deltaTime){};
  ~System() = default;
  void compute();
  void addParticle(Particle particle);
  void printParticles() const;
  const Particle &getParticle(int index) const;
  const std::vector<Particle> &getParticles() const { return _systemParticles; }

protected:
  const std::vector<Particle> &getPrevState() const { return _prevState; }
  std::vector<NBodyEnv::Particle> _prevState;
  std::vector<NBodyEnv::Particle> _systemParticles;
  std::function<void(Particle &, Particle &)> _func;
  T _discretizer;
  double _deltaTime;
};
} // namespace NBodyEnv

#endif
