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
                              NBodyEnv::EulerDiscretizer(), 10.0);

  NBodyEnv::Particle particleOne(NBodyEnv::gravitational, {0.0, 0.0, 0.0},
                                 {0.0, 0.0, 0.0}, 1.0e10, 10);
  NBodyEnv::Particle particleTwo(NBodyEnv::gravitational, {0.0, -1000.0, 0.0},
                                 {0.0, 0.0, 0.0}, 1.0e10, 10);

  testSystem.addParticle(particleOne);
  testSystem.addParticle(particleTwo);

  // Create exporter
  NBodyEnv::Exporter exporter("test.part", 100.0);

  // Create Simulator
  NBodyEnv::Simulator<NBodyEnv::EulerDiscretizer> simulator(
      testSystem, &exporter, 10000, 100);
  simulator.run();

  exporter.close();

  // Second example
  NBodyEnv::RKDiscretizer rk = NBodyEnv::RKDiscretizer(DISC_BEULER);

  NBodyEnv::System testSystemTwo(NBodyEnv::Functions::getGravFunc(),
                                 rk, 10.0);

  NBodyEnv::Particle particleOneTwo(NBodyEnv::gravitational, {0.0, 0.0, 0.0},
                                 {0.0, 0.0, 0.0}, 1.0e10, 10);
  NBodyEnv::Particle particleTwoTwo(NBodyEnv::gravitational, {0.0, -1000.0, 0.0},
                                 {0.0, 0.0, 0.0}, 1.0e10, 10);

  testSystemTwo.addParticle(particleOne);
  testSystemTwo.addParticle(particleTwo);

  // Create exporter
  NBodyEnv::Exporter exporterTwo("test2.part", 100.0);

  // Create Simulator
  NBodyEnv::Simulator<NBodyEnv::RKDiscretizer> simulatorTwo(
      testSystemTwo, &exporterTwo, 10000, 100);
  simulatorTwo.run();

  exporterTwo.close();

  return 0;
}
