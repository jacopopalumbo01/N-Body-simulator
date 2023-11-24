#include "System.hpp"
#include <iostream>

namespace NBodyEnv {
void System::addParticle(Particle particle) {
  _systemParticles.push_back(particle);
}

const Particle &System::getParticle(int index) const {
  return _systemParticles[index];
}

void System::compute() {
  for (auto iter = _systemParticles.begin(); iter != _systemParticles.end();
       iter++) {
    for (auto secIter = iter + 1; secIter != _systemParticles.end();
         secIter++) {
      // Compute new data
    }
  }
}
} // namespace NBodyEnv
