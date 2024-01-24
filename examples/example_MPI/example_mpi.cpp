#include <iostream>
#include <N-Body-sim.hpp>
#include <random>


int main() {
    NBodyEnv::RKDiscretizer rkOne = NBodyEnv::RKDiscretizer(DISC_BEULER);
    NBodyEnv::RKDiscretizer rkTwo = NBodyEnv::RKDiscretizer(DISC_BEULER);

    NBodyEnv::System system(NBodyEnv::Functions::getGravFunc(), rkOne, 10.0);
    NBodyEnv::System systemTwo(NBodyEnv::Functions::getGravFunc(), rkTwo, 10.0);


    constexpr int numParticles = 32;

    // obtain a random number from hardware
    std::random_device rand;
    // seed the generator
    std::mt19937 gen(rand());
    // define the range for particle positions
    std::uniform_real_distribution<> distr(-10000.0, 10000.0);
    // define the range for particle masses
    std::uniform_real_distribution<> massDistr(1.0e10, 1.0e11);


    // Create and add test particles
    for (int i = 0; i < numParticles; i++)
    {
        NBodyEnv::Particle particle(
            NBodyEnv::gravitational,
            {distr(gen), distr(gen), distr(gen)},
            {0.0, 0.0, 0.0}, massDistr(gen), 15);
        system.addParticle(particle);
        systemTwo.addParticle(particle);
    }

    NBodyEnv::Exporter exporter("testMPI.part", 1);
    NBodyEnv::Exporter exporterTwo("test.part", 1);

    
    // MPI version

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);
    for (int i = 0; i < 10; i++)
    {
        exporter.saveState(system.getParticles());
        system.computeMPI();
    }

    exporter.close();
    // Finalize the MPI environment.
    MPI_Finalize();

    // Classic version
    for (int i = 0; i < 10; i++)
    {
        exporterTwo.saveState(systemTwo.getParticles());
        systemTwo.compute();
    }

    exporterTwo.close();
}