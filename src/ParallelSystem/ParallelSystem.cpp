#include "ParallelSystem.hpp"
#include <omp.h>
#include <iostream>

namespace NBodyEnv
{
  void ParallelSystem::addParticle(Particle particle)
  {
    _systemParticles.push_back(particle);
  }

  const Particle &ParallelSystem::getParticle(int index) const
  {
    return _systemParticles[index];
  }

  void ParallelSystem::compute()
  {
    // remember all of this code is enclosed in a parallel region (see example_parallel.cpp, from which this method is called)
#pragma omp for
    // Reset forces
    for (auto iter = _systemParticles.begin(); iter != _systemParticles.end();
         iter++)
    {
      iter->setForce({0.0, 0.0, 0.0});
    }

#pragma omp for
    // compute forces
    for (long unsigned int i = 0; i < _systemParticles.size(); ++i)
    {
      for (long unsigned int j = i + 1; j < _systemParticles.size(); ++j)
      {
        _systemParticles[i].computeForce(_systemParticles[j], _func);
      }
    }

#pragma omp for
    // need to decouple the update of the position and velocity from the computation of the forces, for unknown reasons
    for (auto iter = _systemParticles.begin(); iter != _systemParticles.end();
         iter++)
    {
      // Update position
      iter->updatePos(_deltaTime);
      // Update velocity
      iter->updateVel(_deltaTime);
    }
  }
} // namespace NBodyEnv
