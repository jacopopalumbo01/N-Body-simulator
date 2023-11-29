#include "../../src/Exporter/Exporter.hpp"
#include "../../src/Functions/Functions.hpp"
#include "../../src/Particle/Particle.hpp"
#include "../../src/System/System.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  NBodyEnv::System testSystem(NBodyEnv::Functions::getGravFunc(), 1.0);

  NBodyEnv::Particle particleOne(NBodyEnv::gravitational, {0, 0, 0}, {0, 0, 0},
                                 2e30, 0.5);
  NBodyEnv::Particle particleTwo(NBodyEnv::gravitational, {0, 15e7, 0},
                                 {29722, 0, 0}, 6e24, 0.5);

  testSystem.addParticle(particleOne);
  testSystem.addParticle(particleTwo);

  // Create exporter
  NBodyEnv::Exporter exporter("test.part", 0.5);

  for (int i = 0; i < 10000; i++) {
    testSystem.compute();
    exporter.saveState(testSystem.getParticles());
  }

  exporter.close();

  return 0;
}
