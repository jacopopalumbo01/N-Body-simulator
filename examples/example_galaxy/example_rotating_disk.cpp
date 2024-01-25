#include <N-Body-sim.hpp>
#include <iostream>
#include <random>
#include <omp.h>

int main(int argc, char *argv[])
{
    // create a new ParticleSystem by passing the function which computes the gravitational force
    // the integration method to approximate the position numerically
    // and the time step used for the simulation over time
    NBodyEnv::System<NBodyEnv::VerletDiscretizer> system(NBodyEnv::Functions::getGravFunc(), NBodyEnv::VerletDiscretizer(), 1);

    constexpr int numParticles = 2048;
    constexpr int timeSteps = 3600;


    // obtain a random number from hardware
    std::random_device rand;
    // seed the generator
    std::mt19937 gen(rand());
    // define the range for particle positions
    std::uniform_real_distribution<> distr(-4000.0, 4000.0);
    // define the range for particle masses
    std::uniform_real_distribution<> massDistr(1.0e10, 1.0e11);

    // Create right upper cluster
    for (int i = 0; i < numParticles/4; i++)
    {
        NBodyEnv::Particle particle(
            NBodyEnv::gravitational,
            {1e3 + distr(gen), 1e3 + distr(gen), distr(gen)},
            {0.0, 0.0, 0.0}, massDistr(gen), 30);
        system.addParticle(particle);
    }

    // Create left upper cluster
    for (int i = 0; i < numParticles/4; i++)
    {
        NBodyEnv::Particle particle(
            NBodyEnv::gravitational,
            {-1e3 + distr(gen), 1e3 + distr(gen), distr(gen)},
            {0.0, 0.0, 0.0}, massDistr(gen), 30);
        system.addParticle(particle);
    }

    // Create left lower cluster
    for (int i = 0; i < numParticles/4; i++)
    {
        NBodyEnv::Particle particle(
            NBodyEnv::gravitational,
            {-1e3 + distr(gen), -1e3 + distr(gen), distr(gen)},
            {0.0, 0.0, 0.0}, massDistr(gen), 30);
        system.addParticle(particle);
    }
    
    // Create right lower cluster
    for (int i = 0; i < numParticles/4; i++)
    {
        NBodyEnv::Particle particle(
            NBodyEnv::gravitational,
            {1e3 + distr(gen), -1e3 + distr(gen), distr(gen)},
            {0.0, 0.0, 0.0}, massDistr(gen), 30);
        system.addParticle(particle);
    }

    // NBodyEnv::Particle particle(
    //         NBodyEnv::gravitational,
    //         {0.0, 0.0, 0.0},
    //         {0.0, 0.0, 0.0}, 1e15, 50);

    // system.addParticle(particle);

    // Create exporter
    NBodyEnv::Exporter exporter("test.part", 1);
    // NBodyEnv::Exporter serialExporter("serialTest.part", 1);

// set number of threads
#if defined(_OPENMP)
    omp_set_num_threads(16);
    std::cout << "Number of threads: " << omp_get_max_threads() << std::endl;
#endif // _OPENMP

    // simulate over a year time span
    for (int i = 0; i < timeSteps; i++)
    {
        system.compute();
        if (i % 10 == 0)
            exporter.saveState(system.getParticles());
    }

    exporter.close();

    return 0;
}
