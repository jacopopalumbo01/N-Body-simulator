#include "../../inc/Collisions/SphereBoundary.hpp"
#include "../../inc/Exporter/Exporter.hpp"
#include "../../inc/Functions/Functions.hpp"
#include "../../inc/Particle/Particle.hpp"
#include "../../inc/System/System.hpp"
#include <iostream>

int main(int argc, char *argv[]) {

  // Create a sphere boundary
  NBodyEnv::SphereBoundary boundary({0.0, 0.0, 0.0}, 1e10);

  NBodyEnv::System testSystem(NBodyEnv::Functions::getGravFunc(), 1.0);

  NBodyEnv::Particle particleOne(NBodyEnv::gravitational, {0.0, 0.0, 0.0},
                                 {5e-3, 0.0, 0.0}, 1.0e10, 50);
  NBodyEnv::Particle particleTwo(NBodyEnv::gravitational, {0.0, -1000.0, 0.0},
                                 {-5e-3, 0.0, 0.0}, 1.0e10, 50);

  testSystem.addParticle(particleOne);
  testSystem.addParticle(particleTwo);

  // Create exporter
  NBodyEnv::Exporter exporter("test.part", 1.0);

  for (int i = 0; i < 3600 * 24 * 7; i++) {
    testSystem.compute();
    if (i % 3600 == 0)
      exporter.saveState(testSystem.getParticles());
  }

  exporter.close();

  return 0;
}
