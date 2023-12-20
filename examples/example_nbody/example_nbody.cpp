#include "../../inc/Exporter/Exporter.hpp"
#include "../../inc/Functions/Functions.hpp"
#include "../../inc/Particle/Particle.hpp"
#include "../../inc/System/System.hpp"
#include "../../inc/Collisions/Collisions.hpp"
#include "../../inc/Functions/EulerDiscretizer.hpp"
#include "../../inc/Functions/VerletDiscretizer.hpp"
#include <iostream>
#include <random>
// #include <omp.h>

int main(int argc, char *argv[])
{
    // create a new ParticleSystem by passing the function which computes the gravitational force
    // the integration method to approximate the position numerically 
    // and the time step used for the simulation over time
    NBodyEnv::System<NBodyEnv::VerletDiscretizer> testSystem(NBodyEnv::Functions::getGravFunc(), NBodyEnv::VerletDiscretizer(), 1);

    constexpr int numParticles = 32;

    // obtain a random number from hardware
    std::random_device rand; 
    // seed the generator
    std::mt19937 gen(rand()); 
    // define the range for particle positions
    std::uniform_real_distribution<> distr(-6000.0, 6000.0); 
    // define the range for particle masses
    std::uniform_real_distribution<> massDistr(1.0e10, 1.0e11);

    // Create and add test particles
    for (int i = 0; i < numParticles; i++) {
      NBodyEnv::Particle particle(
          NBodyEnv::gravitational,
          {distr(gen), distr(gen), distr(gen)},
          {0.0, 0.0, 0.0}, massDistr(gen), 15);
      testSystem.addParticle(particle);
    }

    // Create exporter
    NBodyEnv::Exporter exporter("../../../graphics/test.part", 1);

#if defined(_OPENMP)
#pragma omp parallel
#endif
    // simulate over a year time span
    for (int i = 0; i < 3600 * 24 * 14; i++)
    {
        testSystem.compute();
        if (i % 3600 == 0)
#if defined(_OPENMP)
#pragma omp single
#endif
            exporter.saveState(testSystem.getParticles());
    }

    exporter.close();

    return 0;
}
