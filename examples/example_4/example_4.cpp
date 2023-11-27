#include "../../src/Functions/Functions.hpp"
#include "../../src/Particle/Particle.hpp"
#include "../../src/System/System.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  NBodyEnv::System testSystem(NBodyEnv::Functions::getGravFunc(), 1.0);

  NBodyEnv::Particle particleOne(NBodyEnv::gravitational, {0, 0, 0}, {0, 0, 0},
                                 2e30, 1);
  NBodyEnv::Particle particleTwo(NBodyEnv::gravitational, {0, 15e7, 0},
                                 {29722, 0, 0}, 6e24, 1);

  testSystem.addParticle(particleOne);
  testSystem.addParticle(particleTwo);

  for (int i = 0; i < 100; i++) {
    testSystem.compute();
    std::cout << "Step " << i << std::endl;
    std::cout << "Particle 1" << std::endl;
    testSystem.getParticle(0).print();
    std::cout << "Particle 2" << std::endl;
    testSystem.getParticle(1).print();
  }

  return 0;
}
