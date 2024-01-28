#include <N-Body-sim.hpp>
#include <iostream>
#include <random>
#include <chrono>
#include <omp.h>

int main()
{
    using namespace std::chrono;

    NBodyEnv::RKDiscretizer rkOne = NBodyEnv::RKDiscretizer(DISC_FEULER);
    NBodyEnv::RKDiscretizer rkTwo = NBodyEnv::RKDiscretizer(DISC_BEULER);

    // NBodyEnv::System system(NBodyEnv::Functions::getGravFunc(), rkOne, 10.0);
    NBodyEnv::System systemSerial(NBodyEnv::Functions::getGravFunc(), NBodyEnv::EulerDiscretizer(), 1.0);
    NBodyEnv::System system(NBodyEnv::Functions::getGravFunc(), rkOne, 1.0);

    constexpr int numParticles = 256;

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
        systemSerial.addParticle(particle);
    }

    NBodyEnv::Exporter exporter("testMPI.part", 1);
    NBodyEnv::Exporter exporterTwo("test.part", 1);

    // set number of threads
#if defined(_OPENMP)
    omp_set_num_threads(8);
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
        std::cout << "Computing with mpi-openMP hybrid. Number of nodes: " << world_size << std::endl;
#if defined(_OPENMP)
        std::cout << "Number of threads: " << omp_get_max_threads() << std::endl;
#endif // _OPENMP
    }

    auto start = high_resolution_clock::now();

    for (int i = 0; i < 100; i++)
    {
        system.computeMPI();
        if (world_rank == 0 && (i % 10 == 0)) // Only master exports
            exporter.saveState(system.getParticles());
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
    omp_set_num_threads(1);
#endif // _OPENMP

    start = high_resolution_clock::now();

    if (world_rank == 0)
    {
        // Classic serial version
        for (int i = 0; i < 100; i++)
        {
            systemSerial.computeSerial();
            if (i % 10 == 0)
                exporterTwo.saveState(systemSerial.getParticles());
        }
    }

    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    if (world_rank == 0)
    {
        std::cout << "Time taken by serial execution: "
                  << duration.count() << " milliseconds" << std::endl;
    }

    exporterTwo.close();

    // Finalize the MPI environment.
    MPI_Finalize();
}