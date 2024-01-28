#include "Exporter/Exporter.hpp"
#include "Functions/EulerDiscretizer.hpp"
#include "Functions/Functions.hpp"
#include "Functions/VerletDiscretizer.hpp"
#include "Particle/Particle.hpp"
#include "Simulator/Simulator.hpp"
#include "System/System.hpp"
#include <iostream>

int main(int argc, char *argv[]) {

  NBodyEnv::System testSystem(NBodyEnv::Functions::getGravFunc(),
                              NBodyEnv::VerletDiscretizer(), 1.0);

  NBodyEnv::Particle particleOne(NBodyEnv::gravitational, {0.0, 0.0, 0.0},
                                 {5e-3, 0.0, 0.0}, 1.0e10, 50);
  NBodyEnv::Particle particleTwo(NBodyEnv::gravitational, {0.0, -1000.0, 0.0},
                                 {-5e-3, 0.0, 0.0}, 1.0e10, 50);

  testSystem.addParticle(particleOne);
  testSystem.addParticle(particleTwo);

  // Create exporter
  NBodyEnv::Exporter exporter("test.part", 1.0);

  // Create Simulator
  NBodyEnv::Simulator<NBodyEnv::VerletDiscretizer> simulator(
      testSystem, &exporter, 1000, 10);
  simulator.run();

  exporter.close();

  return 0;
}
