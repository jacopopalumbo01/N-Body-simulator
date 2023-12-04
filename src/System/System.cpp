#include "System.hpp"

namespace NBodyEnv {
void System::addParticle(Particle particle) {
  _systemParticles.push_back(particle);
}

void System::addParticle(ParticleVerlet particleVerlet) {
  _systemVerlet.push_back(particleVerlet);
}

const Particle &System::getParticle(int index) const {
  return _systemParticles[index];
}

const ParticleVerlet &System::getParticleVerlet(int index) const {
  return _systemVerlet[index];
}

void System::compute() {

  // Reset forces
  for (auto iter = _systemParticles.begin(); iter != _systemParticles.end();
       iter++) {
    iter->setForce({0.0, 0.0, 0.0});
  }

  // Compute system forces
  for (auto iter = _systemParticles.begin(); iter != _systemParticles.end();
       iter++) {

    for (auto secIter = iter + 1; secIter != _systemParticles.end();
         secIter++) {
      // Compute new force
      iter->computeForce(*secIter, _func);
    }

    // Update position
    iter->updatePos(_deltaTime);

    // Update velocity
    iter->updateVel(_deltaTime);
  }
}

void System::computeVerlet(){
  for (auto iter = _systemVerlet.begin(); iter != _systemVerlet.end();
       iter++) {
    iter->setForce({0.0, 0.0, 0.0});
  }

  // Compute system forces
  for (auto iter = _systemVerlet.begin(); iter != _systemVerlet.end();
       iter++) {

    for (auto secIter = iter + 1; secIter != _systemVerlet.end();
         secIter++) {
      // Compute new force
      iter->computeForce(*secIter, _funcVerlet);
    }

    iter->updateAcc();

    if(iter->getPrevPart().xPos==0 && iter->getPrevPart().yPos==0 && iter->getPrevPart().zPos==0){
      iter->updateFirstPos(_deltaTime);
    }
    else{
      iter->updatePos(_deltaTime);
    }
  }
}

void System::printParticles() const{
  for(auto iter=_systemParticles.begin(); iter != _systemParticles.end(); iter++){
    std::cout << "Particle number " << iter.base() << " in the system" << std::endl;
  }  
}

void System::printParticlesVerlet() const{
  for(auto iter=_systemVerlet.begin(); iter != _systemVerlet.end(); iter++){
    std::cout << "Particle number " << iter.base() << " in the system" << std::endl;
  }  
}

} // namespace NBodyEnv
