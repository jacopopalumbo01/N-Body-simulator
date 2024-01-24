#include <iostream>
#include <N-Body-sim.hpp>
#include <random>


int main() {
    NBodyEnv::RKDiscretizer rkOne = NBodyEnv::RKDiscretizer(DISC_BEULER);
    NBodyEnv::RKDiscretizer rkTwo = NBodyEnv::RKDiscretizer(DISC_BEULER);

    NBodyEnv::System system(NBodyEnv::Functions::getGravFunc(), rkOne, 10.0);
    NBodyEnv::System systemTwo(NBodyEnv::Functions::getGravFunc(), NBodyEnv::VerletDiscretizer(), 10.0);


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

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    std::cout << "Computing with mpi. Number of nodes: " << world_size << std::endl;

    for (int i = 0; i < 1000; i++)
    {
        if(world_rank == 0 && i % 100 == 0) // Only master exports
            exporter.saveState(system.getParticles());

        system.computeMPI();
        MPI_Barrier(MPI_COMM_WORLD);
    }

    exporter.close();
    

    if (world_rank == 0){
        // Classic version
        for (int i = 0; i < 1000; i++)
        {
            if(i % 100 == 0)
                exporterTwo.saveState(systemTwo.getParticles());
            systemTwo.compute();
        }
    }

    exporterTwo.close();

    // Finalize the MPI environment.
    MPI_Finalize();
}