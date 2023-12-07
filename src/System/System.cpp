#include "../../inc/System/System.hpp"

namespace NBodyEnv
{
  void System::addParticle(Particle particle)
  {
    _systemParticles.push_back(particle);
    _prevState.push_back(particle);
  }

  void System::addParticle(ParticleVerlet particleVerlet)
  {
    _systemVerlet.push_back(particleVerlet);
  }

  const Particle &System::getParticle(int index) const
  {
    return _systemParticles[index];
  }

  const ParticleVerlet &System::getParticleVerlet(int index) const
  {
    return _systemVerlet[index];
  }

  void System::compute()
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
    for (auto iter = _systemParticles.begin(); iter != _systemParticles.end();
         iter++)
    {
      bool isP2Visible = true;
      if (!iter->getVisible())
      {
        // particle is not visible, it has previously been absorbed by another particle
        // ==> skip it
        // std::cout << "Particle in position: " << iter->getPos().xPos << ", "
        //           << iter->getPos().yPos << ", " << iter->getPos().zPos << " has been absorbed" << std::endl;
        continue;
      }
      for (auto secIter = iter + 1; secIter != _systemParticles.end();
           secIter++)
      {
        // here we still need to call computeForce() on the particle p2, even if it is not visible
        // otherwise we won't update p1
        iter->computeForce(*secIter, _func);
        if (secIter->getVisible() == false)
          isP2Visible = false;
      }
      if(!isP2Visible) {
        // print iter velocity
        // std::cout << "p1 velocity after collision: " << iter->getVel().xVel << ", " << iter->getVel().yVel << ", " << iter->getVel().zVel << std::endl;
      }

      // Update position
      iter->updatePos(_deltaTime);

      // Update velocity
      iter->updateVel(_deltaTime);
    }

    // Update prev state
    _prevState.clear();
    std::copy(tempState.begin(), tempState.end(), _prevState.begin());
  }

  void System::computeVerlet()
  {
    for (auto iter = _systemVerlet.begin(); iter != _systemVerlet.end();
         iter++)
    {
      iter->setForce({0.0, 0.0, 0.0});
    }

    // Compute system forces
    for (auto iter = _systemVerlet.begin(); iter != _systemVerlet.end();
         iter++)
    {

      for (auto secIter = iter + 1; secIter != _systemVerlet.end();
           secIter++)
      {
        // Compute new force
        iter->computeForce(*secIter, _funcVerlet);
      }

      iter->updateAcc();

      if (iter->getPrevPart().xPos == 0 && iter->getPrevPart().yPos == 0 && iter->getPrevPart().zPos == 0)
      {
        iter->updateFirstPos(_deltaTime);
      }
      else
      {
        iter->updatePos(_deltaTime);
      }
    }
  }

  void System::printParticles() const
  {
    for (auto iter = _systemParticles.begin(); iter != _systemParticles.end(); iter++)
    {
      std::cout << "Particle number " << iter.base() << " in the system" << std::endl;
    }
  }

  void System::printParticlesVerlet() const
  {
    for (auto iter = _systemVerlet.begin(); iter != _systemVerlet.end(); iter++)
    {
      std::cout << "Particle number " << iter.base() << " in the system" << std::endl;
    }
  }

} // namespace NBodyEnv
