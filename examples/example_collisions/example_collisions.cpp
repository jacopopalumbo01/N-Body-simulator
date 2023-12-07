#include "../../inc/Exporter/Exporter.hpp"
#include "../../inc/Functions/Functions.hpp"
#include "../../inc/Particle/Particle.hpp"
#include "../../inc/System/System.hpp"
#include "../../inc/Collisions/Collisions.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  NBodyEnv::System testSystem(NBodyEnv::Functions::getGravFunc(), 1.0);

  NBodyEnv::Particle particleOne(NBodyEnv::gravitational, {0.0, 0.0, 0.0},
                                 {5e-3, 0.0, 0.0}, 2.0e10, 50);
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

  // print p1 mass
  std::cout << "P1 mass: " << testSystem.getParticle(0).getSpecInfo() << std::endl;
  // print p1 radius 
  std::cout << "P1 radius: " << testSystem.getParticle(0).getRadius() << std::endl;

  exporter.close();

  return 0;
}
