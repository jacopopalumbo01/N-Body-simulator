#include <iostream>
#include <N-Body-sim.hpp>
#include <random>
#include <chrono>
#include <omp.h>

int main()
{
    using namespace std::chrono;

    NBodyEnv::RKDiscretizer rkOne = NBodyEnv::RKDiscretizer(DISC_FEULER);
    NBodyEnv::RKDiscretizer rkTwo = NBodyEnv::RKDiscretizer(DISC_BEULER);

    NBodyEnv::System system(NBodyEnv::Functions::getGravFunc(), rkOne, 10.0);
    NBodyEnv::System systemTwo(NBodyEnv::Functions::getGravFunc(), NBodyEnv::EulerDiscretizer(), 10.0);

    constexpr int numParticles = 16;

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

    // set number of threads
#if defined(_OPENMP)
    omp_set_num_threads(1);
#endif // _OPENMP

    // MPI version
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    int world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank == 0)
    {
        std::cout << "Number of OpenMP threads: " << omp_get_max_threads() << std::endl;
        std::cout << "Computing with MPI. Number of nodes: " << world_size << std::endl;
    }

    auto start = high_resolution_clock::now();

    for (int i = 0; i < 10; i++)
    {
        if (world_rank == 0) // Only master exports
            exporter.saveState(system.getParticles());

        system.computeMPI();
        MPI_Barrier(MPI_COMM_WORLD);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    if (world_rank == 0)
    {
        std::cout << "Time taken by MPI OMP hybrid execution: "
                  << duration.count() << " milliseconds" << std::endl;
    }

    exporter.close();

#if defined(_OPENMP)
    omp_set_num_threads(4);
#endif // _OPENMP

    if (world_rank == 0)
    {
        std::cout << "Number of OpenMP threads: " << omp_get_max_threads() << std::endl;
        std::cout << "Computing without MPI " << std::endl;
    }

    start = high_resolution_clock::now();

    if (world_rank == 0)
    {
        // Classic version
        for (int i = 0; i < 10; i++)
        {
            exporterTwo.saveState(systemTwo.getParticles());
            systemTwo.compute();
        }
    }

    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    if (world_rank == 0)
    {
        std::cout << "Time taken by OMP execution: "
                  << duration.count() << " milliseconds" << std::endl;
    }

    exporterTwo.close();

    // Finalize the MPI environment.
    MPI_Finalize();
}