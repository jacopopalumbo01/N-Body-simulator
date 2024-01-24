#ifndef SYSTEM
#define SYSTEM

#include "Particle/Particle.hpp"
#include "Functions/Functions.hpp"
#include "Functions/RKDiscretizer.hpp"
#include "TreeNode/TreeNode.hpp"
#include <functional>
#include <iostream>
#include <vector>

// Serialization 
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/serialization/vector.hpp>

// MPI
#include <mpi.h>

namespace NBodyEnv {
template <class T> class System {
public:
  // Two contructor, one has already the boundaries
  System(std::function<void(Particle &, Particle &)> func, T discretizer,
         double deltaTime, std::vector<double> max, std::vector<double> min)
      : _func(func), _discretizer(discretizer), _deltaTime(deltaTime),
      m_root(NBodyEnv::TreeNode(max, min, nullptr)){};

  System(std::function<void(Particle &, Particle &)> func, T discretizer,
         double deltaTime)
      : _func(func), _discretizer(discretizer), _deltaTime(deltaTime),
      m_root(NBodyEnv::TreeNode({10000.0, 10000.0, 10000.0}, {-10000.0, -10000.0, -10000.0}, nullptr)){};

  ~System() = default;
  void compute();
  void computeMPI();
  void computeBH();
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
  NBodyEnv::TreeNode m_root;
};
} // namespace NBodyEnv

#endif
