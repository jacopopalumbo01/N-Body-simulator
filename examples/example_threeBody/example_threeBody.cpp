#include "../../inc/Exporter/Exporter.hpp"
#include "../../inc/Functions/Functions.hpp"
#include "../../inc/Particle/Particle.hpp"
#include "../../inc/System/System.hpp"
#include "../../inc/Collisions/Collisions.hpp"
#include "../../inc/Functions/EulerDiscretizer.hpp"
#include "../../inc/Functions/VerletDiscretizer.hpp"
#include <iostream>
#include <chrono>
#include <omp.h>

int main(int argc, char *argv[])
{
    using namespace std::chrono;

    // create a new ParticleSystem by passing the function which computes the gravitational force
    // and the time step used for the simulation over time
    NBodyEnv::System<NBodyEnv::VerletDiscretizer> parallelSystem(NBodyEnv::Functions::getGravFunc(), NBodyEnv::VerletDiscretizer(), 1);
    NBodyEnv::System<NBodyEnv::VerletDiscretizer> serialSystem(NBodyEnv::Functions::getGravFunc(), NBodyEnv::VerletDiscretizer(), 1);

    NBodyEnv::Particle particleOne(NBodyEnv::gravitational, {-500.0, 0.0, 0.0},
                                   {0.0, 5e-3, 0.0}, 1.0e10, 10);

    NBodyEnv::Particle particleTwo(NBodyEnv::gravitational, {500.0, 0.0, 0.0},
                                   {0.0, -5e-3, 0.0}, 1.0e10, 10);

    NBodyEnv::Particle particleThree(NBodyEnv::gravitational, {0.0, 0.0, 0.0},
                                     {0.0, 0.0, 0.0}, 1.0e10, 10);

    NBodyEnv::Particle particleFour(NBodyEnv::gravitational, {1800.0, 100.0, 0.0},
                                    {1.0e-3, -4.0e-3, 0.0}, 1.0e10, 10);

    NBodyEnv::Particle particleFive(NBodyEnv::gravitational, {1200.0, -700.0, 0.0},
                                    {-2.0e-3, -1.0e-3, 0.0}, 1.0e10, 10);

    NBodyEnv::Particle particleSix(NBodyEnv::gravitational, {400.0, -900.0, 0.0},
                                   {-6.0e-3, 6.0e-3, 0.0}, 1.0e10, 10);

    NBodyEnv::Particle particleSeven(NBodyEnv::gravitational, {200.0, 0.0, -300.0},
                                     {0.0, 0.0, 0.0}, 1.0e10, 10);

    NBodyEnv::Particle particleEight(NBodyEnv::gravitational, {0.0, 400.0, 900.0},
                                     {0.0, 0.0, 0.0}, 1.0e10, 10);

    NBodyEnv::Particle particleNine(NBodyEnv::gravitational, {-700.0, 0.0, 300.0},
                                    {0.0, 0.0, 0.0}, 1.0e10, 10);

    NBodyEnv::Particle particleTen(NBodyEnv::gravitational, {200.0, 600.0, -1000.0},
                                   {0.0, 0.0, 0.0}, 1.0e10, 10);

    parallelSystem.addParticle(particleOne);
    parallelSystem.addParticle(particleTwo);
    parallelSystem.addParticle(particleThree);
    parallelSystem.addParticle(particleFour);
    parallelSystem.addParticle(particleFive);
    parallelSystem.addParticle(particleSix);
    parallelSystem.addParticle(particleSeven);
    parallelSystem.addParticle(particleEight);
    parallelSystem.addParticle(particleNine);
    parallelSystem.addParticle(particleTen);

    serialSystem.addParticle(particleOne);
    serialSystem.addParticle(particleTwo);
    serialSystem.addParticle(particleThree);
    serialSystem.addParticle(particleFour);
    serialSystem.addParticle(particleFive);
    serialSystem.addParticle(particleSix);
    serialSystem.addParticle(particleSeven);
    serialSystem.addParticle(particleEight);
    serialSystem.addParticle(particleNine);
    serialSystem.addParticle(particleTen);

    // Create exporter
    NBodyEnv::Exporter exporter("test.part", 1);
    NBodyEnv::Exporter serialExporter("serialTest.part", 1);

    // simulate the system many times ==> need this for testing and estimating
    // the speed up of the parallelization with OpenMP
    constexpr int numSimulations = 20;

    // array of microseconds type for each simulation
    microseconds durationsParallel[numSimulations];
    microseconds durationsSerial[numSimulations];

    for (int i = 0; i < numSimulations; i++)
    {
        // Get starting timepoint
        auto start = high_resolution_clock::now();

#if defined(_OPENMP)
#pragma omp parallel num_threads(4)
        #endif
        {
            // simulate over a year time span
            for (int k = 0; k < 3600 * 24; k++)
            {
                parallelSystem.compute();
                if (k % 3600 == 0)
#pragma omp master
                    exporter.saveState(parallelSystem.getParticles());
            }
        }

        auto stop = high_resolution_clock::now();

        // Get duration. Substart timepoints to
        // get duration. To cast it to proper unit
        // use duration cast method
        auto duration = duration_cast<milliseconds>(stop - start);
        durationsParallel[i] = duration;

        std::cout << "Time taken by parallel execution: "
                  << duration.count() << " milliseconds" << std::endl;

        exporter.close();

        start = high_resolution_clock::now();

        // simulate over a year time span
        for (int k = 0; k < 3600 * 24; k++)
        {
            serialSystem.compute();
            if (k % 3600 == 0)
                serialExporter.saveState(serialSystem.getParticles());
        }

        stop = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(stop - start);
        durationsSerial[i] = duration;

        std::cout << "Time taken by serial execution: "
                  << duration.count() << " milliseconds" << std::endl;

        serialExporter.close();
    }

    // compute the average speed up of each simulation
    double averageSpeedUp = 0.0;
    double totSerialTime = 0.0;
    double totParallelTime = 0.0;
    for (int k = 0; k < numSimulations; k++)
    {
        averageSpeedUp += (double)durationsSerial[k].count() / (double)durationsParallel[k].count();
        totSerialTime += (double)durationsSerial[k].count();
        totParallelTime += (double)durationsParallel[k].count();
    }

    // print the average parallel execution time
    std::cout << "Average parallel execution time: " << totParallelTime / (double)numSimulations << std::endl;
    // print the average serial execution time
    std::cout << "Average serial execution time: " << totSerialTime / (double)numSimulations << std::endl;

    std::cout << "Average speed up: " << averageSpeedUp / (double)numSimulations << std::endl;

    return 0;
}
