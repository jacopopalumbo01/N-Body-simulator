#include "Exporter/Exporter.hpp"
#include "Functions/Functions.hpp"
#include "Particle/Particle.hpp"
#include "System/System.hpp"
#include "Collisions/Collisions.hpp"
#include "Functions/EulerDiscretizer.hpp"
#include "Functions/VerletDiscretizer.hpp"
#include <iostream>
#include <random>
#include <chrono>
#include <omp.h>

int main(int argc, char *argv[])
{
    using namespace std::chrono;

    // create a new ParticleSystem by passing the function which computes the gravitational force
    // the integration method to approximate the position numerically
    // and the time step used for the simulation over time
    NBodyEnv::System<NBodyEnv::VerletDiscretizer> parallelSystem(NBodyEnv::Functions::getGravFunc(), NBodyEnv::VerletDiscretizer(), 1);
    // NBodyEnv::System<NBodyEnv::VerletDiscretizer> serialSystem(NBodyEnv::Functions::getGravFunc(), NBodyEnv::VerletDiscretizer(), 1);

    constexpr int numParticles = 256;

    // obtain a random number from hardware
    std::random_device rand;
    // seed the generator
    std::mt19937 gen(rand());
    // define the range for particle positions
    std::uniform_real_distribution<> distr(-6000.0, 6000.0);
    // define the range for particle masses
    std::uniform_real_distribution<> massDistr(1.0e10, 1.0e11);

    // Create and add test particles
    for (int i = 0; i < numParticles; i++)
    {
        NBodyEnv::Particle particle(
            NBodyEnv::gravitational,
            {distr(gen), distr(gen), distr(gen)},
            {0.0, 0.0, 0.0}, massDistr(gen), 15);
        // serialSystem.addParticle(particle);
        parallelSystem.addParticle(particle);
    }

    // simulate the system many times ==> need this for testing and estimating
    // the speed up of the parallelization with OpenMP
    constexpr int numSimulations = 1;

    // array of microseconds type for each simulation
    milliseconds durationsParallel[numSimulations];
    // milliseconds durationsSerial[numSimulations];

    // Create exporter
    NBodyEnv::Exporter exporter("test.part", 1);
    // NBodyEnv::Exporter serialExporter("serialTest.part", 1);

// set number of threads
#if defined(_OPENMP)
    omp_set_num_threads(12);
#endif // _OPENMP

    for (int i = 0; i < numSimulations; i++)
    {
        // Get starting timepoint
        auto start = high_resolution_clock::now();

        // simulate over a year time span
        for (int i = 0; i < 3600; i++)
        {
            parallelSystem.compute();
            if (i % 3600 == 0)
                exporter.saveState(parallelSystem.getParticles());
        }

        auto stop = high_resolution_clock::now();

        // Get duration. Substart timepoints to
        // get duration. To cast it to proper unit
        // use duration cast method
        auto duration = duration_cast<milliseconds>(stop - start);
        durationsParallel[i] = duration;

        std::cout << "Time taken by sequential execution: "
                  << duration.count() << " milliseconds" << std::endl;

        exporter.close();

        // start = high_resolution_clock::now();

        // // simulate over a year time span
        // for (int i = 0; i < 3600 * 24; i++)
        // {
        //     serialSystem.compute();
        //     if (i % 3600 == 0)
        //         serialExporter.saveState(serialSystem.getParticles());
        // }

        // stop = high_resolution_clock::now();
        // duration = duration_cast<milliseconds>(stop - start);
        // durationsSerial[i] = duration;

        // serialExporter.close();

        // std::cout << "Time taken by serial execution: "
        //           << duration.count() << " milliseconds" << std::endl;
    }

    // compute the average speed up of each simulation
    // double averageSpeedUp = 0.0;
    // double totSerialTime = 0.0;
    double totParallelTime = 0.0;
    for (int i = 0; i < numSimulations; i++)
    {
        // averageSpeedUp += (double)durationsSerial[i].count() / (double)durationsParallel[i].count();
        // totSerialTime += (double)durationsSerial[i].count();
        totParallelTime += (double)durationsParallel[i].count();
    }

    // print the average parallel execution time
    std::cout << "Average parallel execution time: " << totParallelTime / (double)numSimulations << std::endl;
    // // print the average serial execution time
    // std::cout << "Average serial execution time: " << totSerialTime / (double)numSimulations << std::endl;

    // std::cout << "Average speed up: " << averageSpeedUp / (double)numSimulations << std::endl;

    return 0;
}
