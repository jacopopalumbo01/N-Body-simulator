#include "Exporter/Exporter.hpp"
#include "Functions/EulerDiscretizer.hpp"
#include "Functions/Functions.hpp"
#include "Functions/VerletDiscretizer.hpp"
#include "Particle/Particle.hpp"
#include "Simulator/Simulator.hpp"
#include "System/System.hpp"
#include "TreeNode/TreeNode.hpp"
#include <omp.h>
#include <iostream>
#include <random>
#include <chrono>

int main(int argc, char *argv[])
{
    using namespace std::chrono;

    // create a new ParticleSystem by passing the function which computes the gravitational force
    // the integration method to approximate the position numerically
    // and the time step used for the simulation over time
    NBodyEnv::System<NBodyEnv::VerletDiscretizer> system(NBodyEnv::Functions::getGravFunc(), NBodyEnv::VerletDiscretizer(), 1);
    NBodyEnv::System<NBodyEnv::VerletDiscretizer> systemBH(NBodyEnv::Functions::getGravFunc(), NBodyEnv::VerletDiscretizer(), 1);
    // NBodyEnv::System<NBodyEnv::VerletDiscretizer> serialSystem(NBodyEnv::Functions::getGravFunc(), NBodyEnv::VerletDiscretizer(), 1);

    constexpr int numParticles = 16384;
    constexpr int timesteps = 3600;

    // Create exporter
    NBodyEnv::Exporter exporter("test.part", 1);
    NBodyEnv::Exporter exporterBH("testBH.part", 1);
    // NBodyEnv::Exporter exporterBH07("testBH07.part", 1);
    // NBodyEnv::Exporter exporterBH10("testBH10.part", 1);

#if defined(_OPENMP)
    omp_set_num_threads(16);
#endif

    // obtain a random number from hardware
    std::random_device rand;
    // seed the generator
    std::mt19937 gen(rand());
    // define the range for particle positions
    std::uniform_real_distribution<> distr(-10000.0, 10000.0);
    // define the range for particle masses
    std::uniform_real_distribution<> massDistr(1.0e10, 1.0e11);

    std::vector<double> max = {50000.0, 50000.0, 50000.0};
    std::vector<double> min = {-50000.0, -50000.0, -50000.0};

    NBodyEnv::TreeNode root(NBodyEnv::TreeNode(max, min, nullptr));

    // Create and add test particles
    for (int i = 0; i < numParticles; i++)
    {
        NBodyEnv::Particle particle(
            NBodyEnv::gravitational,
            {distr(gen), distr(gen), distr(gen)},
            {0.0, 0.0, 0.0}, massDistr(gen), 15);
        system.addParticle(particle);
        systemBH.addParticle(particle);
    }

    // simulate over a year time span
    // Get starting timepoint
    auto start = high_resolution_clock::now();
    for (int i = 0; i < timesteps; i++)
    {
        // compute with direct-sum algorithm
        system.compute();
        // if (i % 36 == 0)
        // {
        //     exporter.saveState(system.getParticles());
        // }
    }

    auto stop = high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    auto durationDS = duration_cast<milliseconds>(stop - start);

    std::cout << "Time taken by standard execution: "
              << durationDS.count() << " milliseconds" << std::endl;

    // exporter.close();

    std::vector<double> theta_vec = {0.5, 0.7, 1.0};

    // loop over all theta values and simulate the system
    for(size_t i = 0; i < theta_vec.size(); i++)
    {
        root.SetTheta(theta_vec[i]);
        start = high_resolution_clock::now();
        for (int i = 0; i < timesteps; i++)
        {
            // compute with Barnes-Hut algorithm
            systemBH.computeBH();
            // if(i % 36 == 0)
            // {
            //     exporterBH.saveState(systemBH.getParticles());
            // }
        }

        stop = high_resolution_clock::now();

        // Get duration. Substart timepoints to
        // get duration. To cast it to proper unit
        // use duration cast method
        auto durationBH = duration_cast<milliseconds>(stop - start);

        std::cout << "Theta = " << root.GetTheta() << " - Time taken by BH execution: "
                << durationBH.count() << " milliseconds" << std::endl;

        // print speedup between direct-sum DS and Barnes-Hut BH algorithm
        std::cout << "Speedup: " << (double)durationDS.count() / (double)durationBH.count() << std::endl;
    }

    // exporterBH.close();

    return 0;
}
