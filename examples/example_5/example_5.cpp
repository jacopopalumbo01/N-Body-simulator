#include "../../inc/Exporter/Exporter.hpp"
#include "../../inc/Functions/Functions.hpp"
#include "../../inc/Particle/Particle.hpp"
#include "../../inc/Particle/ParticleVerlet.hpp"
#include "../../inc/System/System.hpp"
#include <iostream>

int main(int argc, char *argv[]) {

  NBodyEnv::System testSystem(NBodyEnv::Functions::getGravFuncVerlet(), 1.0);

  NBodyEnv::ParticleVerlet particleOne(NBodyEnv::gravitational, {0.0, 0.0, 0.0},
                                 {5e-3, 0.0, 0.0}, 1.0e10, 50, {0.0, 0.0, 0.0});
  NBodyEnv::ParticleVerlet particleTwo(NBodyEnv::gravitational, {0.0, -1000.0, 0.0},
                                 {-5e-3, 0.0, 0.0}, 1.0e10, 50, {0.0, 0.0, 0.0});

  testSystem.addParticle(particleOne);
  testSystem.addParticle(particleTwo);


  //Create exporter
  NBodyEnv::Exporter exporter("../../../graphics/testVerlet.part", 1.0);

  for (int i = 0; i < 3600 * 24 * 7; i++) {
    testSystem.computeVerlet();
    if (i % 3600 == 0)
      exporter.saveState(testSystem.getParticlesVerlet());
  }

  exporter.close();


  return 0;
}
