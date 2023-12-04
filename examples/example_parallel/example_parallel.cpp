#include "../../src/Functions/Functions.hpp"
#include "../../src/Particle/Particle.hpp"
#include "../../src/ParallelSystem/ParallelSystem.hpp"
#include "../../src/Exporter/Exporter.hpp"

#include <iostream>
#include <omp.h>

int main(int argc, char *argv[])
{
  NBodyEnv::ParallelSystem testSystem(NBodyEnv::Functions::getGravFunc(), 1.0);

  NBodyEnv::Particle particleOne(NBodyEnv::gravitational, {0.0, 0.0, 0.0},
                                 {5e-3, 0.0, 0.0}, 1.0e10, 50);
  NBodyEnv::Particle particleTwo(NBodyEnv::gravitational, {0.0, -1000.0, 0.0},
                                 {-5e-3, 0.0, 0.0}, 1.0e10, 50);
  // NBodyEnv::Particle particleThree(NBodyEnv::gravitational, {100.0, 0.0, 0.0},
  //                                  {5e-3, 0.0, 0.0}, 1.0e10, 50);
  // NBodyEnv::Particle particleFour(NBodyEnv::gravitational, {100.0, -1000.0, 0.0},
  //                                 {-5e-3, 0.0, 0.0}, 1.0e10, 50);

  testSystem.addParticle(particleOne);
  testSystem.addParticle(particleTwo);
  // testSystem.addParticle(particleThree);
  // testSystem.addParticle(particleFour);

  // Create exporter
  NBodyEnv::Exporter exporter("test.part", 1.0);

  // #pragma omp parallel
  //   for (int i = 0; i < 3600; i++)
  //   {
  //     testSystem.compute();
  //     if (i % 36 == 0)
  // #pragma omp single
  //       // just one thread should save the state
  //       exporter.saveState(testSystem.getParticles());
  //   }    

#pragma omp parallel
  for (int i = 0; i < 3600 * 24 * 7; i++)
  {
    testSystem.compute();
    if (i % 3600 == 0)
#pragma omp single
      // just one thread should save the state
      exporter.saveState(testSystem.getParticles());
  }

  exporter.close();

  return 0;
}
