#include <N-Body-sim.hpp>
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
    NBodyEnv::System<NBodyEnv::VerletDiscretizer> serialSystem(NBodyEnv::Functions::getGravFunc(), NBodyEnv::VerletDiscretizer(), 1);

    constexpr int numParticles = 128;
    constexpr int timeSteps = 8000;

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
            {0.0, 0.0, 0.0}, massDistr(gen), 30);
        serialSystem.addParticle(particle);
        parallelSystem.addParticle(particle);
    }

    // simulate the system many times ==> need this for testing and estimating
    // the speed up of the parallelization with OpenMP
    constexpr int numSimulations = 6 * 5;

    // array of microseconds type for each simulation
    milliseconds durationsParallel2[numSimulations];
    milliseconds durationsParallel4[numSimulations];
    milliseconds durationsParallel6[numSimulations];
    milliseconds durationsParallel8[numSimulations];
    milliseconds durationsParallel12[numSimulations];
    milliseconds durationsParallel16[numSimulations];
    milliseconds durationsSerial[numSimulations];

    // Create exporter
    // NBodyEnv::Exporter exporter("test.part", 30);
    // NBodyEnv::Exporter serialExporter("serialTest.part", 1);
    int numThreads = 1;
    for (int i = 0; i < numSimulations; i++)
    {
        if (i < 5)
            numThreads = 2;
        else if (i >= 5 && i < 10)
            numThreads = 4;
        else if (i >= 10 && i < 15)
            numThreads = 6;
        else if (i >= 15 && i < 20)
            numThreads = 8;
        else if (i >= 20 && i < 25)
            numThreads = 12;
        else if (i >= 25)
            numThreads = 16;
// set number of threads
#if defined(_OPENMP)
        omp_set_num_threads(numThreads);
#endif // _OPENMP

        // Get starting timepoint
        auto start = high_resolution_clock::now();

        // simulate over a year time span
        for (int i = 0; i < timeSteps; i++)
        {
            parallelSystem.compute();
        }

        auto stop = high_resolution_clock::now();

        // // Get duration. Substart timepoints to
        // // get duration. To cast it to proper unit
        // // use duration cast method
        auto duration = duration_cast<milliseconds>(stop - start);
        if (i < 5)
            durationsParallel2[i] = duration;
        else if (i >= 5 && i < 10)
            durationsParallel4[i] = duration;
        else if (i >= 10 && i < 15)
            durationsParallel6[i] = duration;
        else if (i >= 15 && i < 20)
            durationsParallel8[i] = duration;
        else if (i >= 20 && i < 25)
            durationsParallel12[i] = duration;
        else if (i >= 25)
            durationsParallel16[i] = duration;

        if (i < 5)
        {
            start = high_resolution_clock::now();
            // simulate over a year time span
            for (int i = 0; i < timeSteps; i++)
            {
                serialSystem.computeSerial();
            }

            stop = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(stop - start);
            durationsSerial[i] = duration;
        }
    }

    // compute the average speed up of each simulation
    double totSerialTime = 0.0;
    double totParallelTime2 = 0.0;
    double totParallelTime4 = 0.0;
    double totParallelTime6 = 0.0;
    double totParallelTime8 = 0.0;
    double totParallelTime12 = 0.0;
    double totParallelTime16 = 0.0;
    for (int i = 0; i < numSimulations; i++)
    {
        totSerialTime += (double)durationsSerial[i].count();
        totParallelTime2 += (double)durationsParallel2[i].count();
        totParallelTime4 += (double)durationsParallel4[i].count();
        totParallelTime6 += (double)durationsParallel6[i].count();
        totParallelTime8 += (double)durationsParallel8[i].count();
        totParallelTime12 += (double)durationsParallel12[i].count();
        totParallelTime16 += (double)durationsParallel16[i].count();
    }

    // print the average parallel execution time
    std::cout << "Average parallel execution time with 2 threads: " << totParallelTime2 / 5 << std::endl;
    std::cout << "Average parallel execution time with 4 threads: " << totParallelTime4 / 5 << std::endl;
    std::cout << "Average parallel execution time with 6 threads: " << totParallelTime6 / 5 << std::endl;
    std::cout << "Average parallel execution time with 8 threads: " << totParallelTime8 / 5 << std::endl;
    std::cout << "Average parallel execution time with 12 threads: " << totParallelTime12 / 5 << std::endl;
    std::cout << "Average parallel execution time with 16 threads: " << totParallelTime16 / 5 << std::endl;
    // print the average serial execution time
    std::cout << "Average serial execution time: " << totSerialTime / 5 << std::endl;

    std::cout << "Average speed up with 2 threads: " << totSerialTime / totParallelTime2 << std::endl;
    std::cout << "Average speed up with 4 threads: " << totSerialTime / totParallelTime4 << std::endl;
    std::cout << "Average speed up with 6 threads: " << totSerialTime / totParallelTime6 << std::endl;
    std::cout << "Average speed up with 8 threads: " << totSerialTime / totParallelTime8 << std::endl;
    std::cout << "Average speed up with 12 threads: " << totSerialTime / totParallelTime12 << std::endl;
    std::cout << "Average speed up with 16 threads: " << totSerialTime / totParallelTime16 << std::endl;

    return 0;
}
