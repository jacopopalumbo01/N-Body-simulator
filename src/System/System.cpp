#include "../../inc/System/System.hpp"
#include "../../inc/Particle/Particle.hpp"
#include "../../inc/Functions/EulerDiscretizer.hpp"
#include "../../inc/Functions/VerletDiscretizer.hpp"

namespace NBodyEnv
{

  // TODO FIX TEMPLATE

  template <>
  void System<EulerDiscretizer>::addParticle(Particle particle)
  {
    _systemParticles.push_back(particle);
    _prevState.push_back(particle);
  }

  template <>
  const Particle &System<EulerDiscretizer>::getParticle(int index) const
  {
    return _systemParticles[index];
  }

  template <>
  void System<EulerDiscretizer>::printParticles() const
  {
    for (auto iter = _systemParticles.begin(); iter != _systemParticles.end(); iter++)
    {
      std::cout << "Particle number " << iter.base() << " in the system" << std::endl;
    }
  }

  template <>
  void System<EulerDiscretizer>::compute()
  {
    // Save current state in a temp vector
    std::vector<NBodyEnv::Particle> tempState(_systemParticles);

    // Reset forces
    for (auto iter = _systemParticles.begin(); iter != _systemParticles.end();
         iter++)
    {
      iter->setForce({0.0, 0.0, 0.0});
    }

    // boolean flag to make sure particle is updated in case all others have been absorbed
    bool updated = false;

    // Compute system forces
    for (auto iter = _systemParticles.begin(); iter != _systemParticles.end();
         iter++)
    {
      if (!iter->getVisible())
      {
        // particle is not visible, it has previously been absorbed by another particle
        // ==> skip it
        continue;
      }
      // reset the updated flag
      updated = false;

      for (auto secIter = iter + 1; secIter != _systemParticles.end();
           secIter++)
      {
        // if p2 is not visible, don't compute the force between it and p1
        if (secIter->getVisible() == false)
          continue;
        iter->computeForce(*secIter, _func);
        updated = true;
      }
      if (!updated)
      {
        // all particles have been absorbed by p1, therefore they are not visible ==> the computeForce method in the loop
        // above has not been called, and the force on p1 has not been updated ==> we need to update it here with a ghostParticle
        NBodyEnv::Particle ghostParticle(NBodyEnv::gravitational, {0.0, 0.0, 0.0},
                                         {0.0, 0.0, 0.0}, 0, 0);
        iter->computeForce(ghostParticle, _func);
        // let the user know it's system collapsed into one particle and cut the loop short, no need to update
        // the position of the other particles since they are not visible
        std::cout << "Particle " << iter.base() << " has absorbed all other particles" << std::endl;
        break;
      }
      _discretizer.discretize(*iter, _deltaTime);
    }
  }

  template <>
  void System<VerletDiscretizer>::addParticle(Particle particle)
  {
    _systemParticles.push_back(particle);
    _prevState.push_back(particle);
  }

  template <>
  const Particle &System<VerletDiscretizer>::getParticle(int index) const
  {
    return _systemParticles[index];
  }

  template <>
  void System<VerletDiscretizer>::printParticles() const
  {
    for (auto iter = _systemParticles.begin(); iter != _systemParticles.end(); iter++)
    {
      std::cout << "Particle number " << iter.base() << " in the system" << std::endl;
    }
  }

  // TODO the same as above for the collisions

  template <>
  void System<VerletDiscretizer>::compute()
  {
    // Save current state in a temp vector
    std::vector<NBodyEnv::Particle> tempState(_systemParticles);

    // Reset forces
    for (auto iter = _systemParticles.begin(); iter != _systemParticles.end();
         iter++)
    {
      iter->setForce({0.0, 0.0, 0.0});
    }

    // Compute system forces
    for (auto iter = _systemParticles.begin(), prevIter = _prevState.begin(); iter != _systemParticles.end();
         iter++, prevIter++)
    {

      for (auto secIter = iter + 1; secIter != _systemParticles.end();
           secIter++)
      {
        // Compute new force
        iter->computeForce(*secIter, _func);
      }

      if (prevIter->getPos().xPos == 0 && prevIter->getPos().yPos == 0 && prevIter->getPos().zPos == 0)
      {
        _discretizer.updateFirsePos(*iter, _deltaTime);
      }
      else
      {
        _discretizer.updatePos(*iter, *prevIter, _deltaTime);
      }
    }

    // Update prev state
    _prevState.clear();
    std::copy(tempState.begin(), tempState.end(), _prevState.begin());
  }
} // namespace NBodyEnv
