#include "../../inc/System/System.hpp"
#include "../../inc/Functions/EulerDiscretizer.hpp"

namespace NBodyEnv {

template<>
void System<EulerDiscretizer>::addParticle(Particle particle) {
  _systemParticles.push_back(particle);
  _prevState.push_back(particle);
}

template<>
const Particle &System<EulerDiscretizer>::getParticle(int index) const {
  return _systemParticles[index];
}

template<>
void System<EulerDiscretizer>::compute() {
  // Save current state in a temp vector
  std::vector<NBodyEnv::Particle> tempState(_systemParticles);

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

    iter->discretize(*iter, _discretizer.discretize, _deltaTime);
  }

  // Update prev state
  _prevState.clear();
  std::copy(tempState.begin(), tempState.end(), _prevState.begin());
}

template<>
void System<EulerDiscretizer>::printParticles() const{
  for(auto iter=_systemParticles.begin(); iter != _systemParticles.end(); iter++){
    std::cout << "Particle number " << iter.base() << " in the system" << std::endl;
  }  
}

} // namespace NBodyEnv
