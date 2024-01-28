#include <N-Body-sim.hpp>
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

    // PERFORMANCE TESTING FOR SPEED UP EVALUATION
    constexpr int numParticles_sim = 32768;
    constexpr int timesteps_sim = 1;
    constexpr int num_sim = 5;

#if defined(_OPENMP)
    omp_set_num_threads(16);
#endif

    for (int i = 0; i < numParticles_sim; i++)
    {
        NBodyEnv::Particle particle(
            NBodyEnv::gravitational,
            {distr(gen), distr(gen), distr(gen)},
            {0.0, 0.0, 0.0}, massDistr(gen), 40);
        system.addParticle(particle);
        systemBH.addParticle(particle);
    }

    milliseconds durationsDS[num_sim];
    milliseconds durationsBH05[num_sim];
    milliseconds durationsBH07[num_sim];
    milliseconds durationsBH10[num_sim];

    std::vector<double> theta_vec = {0.5, 0.7, 1.0};

    for (int k = 0; k < num_sim; ++k)
    {
        auto start = high_resolution_clock::now();
        for (int i = 0; i < timesteps_sim; i++)
        {
            // compute with direct-sum algorithm
            system.compute();
        }

        auto stop = high_resolution_clock::now();

        // Get duration. Substart timepoints to
        // get duration. To cast it to proper unit
        // use duration cast method
        auto durationDSparallel = duration_cast<milliseconds>(stop - start);
        durationsDS[k] = durationDSparallel;

        std::cout << "Time taken by parallel execution: "
                  << durationDSparallel.count() << " milliseconds" << std::endl;

       // loop over all theta values and simulate the system
        for (size_t i = 0; i < theta_vec.size(); i++)
        {
            root.SetTheta(theta_vec[i]);
            auto start = high_resolution_clock::now();
            for (int j = 0; j < timesteps_sim; j++)
            {
                // compute with Barnes-Hut algorithm
                systemBH.computeBH();
            }

            auto stop = high_resolution_clock::now();

            // Get duration. Substart timepoints to
            // get duration. To cast it to proper unit
            // use duration cast method
            auto durationBH = duration_cast<milliseconds>(stop - start);

            if (theta_vec[i] == 0.5)
            {
                durationsBH05[k] = durationBH;
            }
            else if (theta_vec[i] == 0.7)
            {
                durationsBH07[k] = durationBH;
            }
            else if (theta_vec[i] == 1.0)
            {
                durationsBH10[k] = durationBH;
            }
        }
    }

    double totParallelTime = 0.0;
    double averageSpeedUp05 = 0.0;
    double averageSpeedUp07 = 0.0;
    double averageSpeedUp10 = 0.0;
    double totTime05 = 0.0;
    double totTime07 = 0.0;
    double totTime10 = 0.0;
    for (size_t i = 0; i < num_sim; i++)
    {
        averageSpeedUp05 += (double)durationsDS[i].count() / (double)durationsBH05[i].count();
        averageSpeedUp07 += (double)durationsDS[i].count() / (double)durationsBH07[i].count();
        averageSpeedUp10 += (double)durationsDS[i].count() / (double)durationsBH10[i].count();
        totTime05 += (double)durationsBH05[i].count();
        totTime07 += (double)durationsBH07[i].count();
        totTime10 += (double)durationsBH10[i].count();
        totParallelTime += (double)durationsDS[i].count();
    }

    // print the average parallel execution time
    std::cout << "Average parallel execution time: " << totParallelTime / (double)num_sim << std::endl;
    std::cout << "Average BH execution time for theta = 0.5: " << totTime05 / (double)num_sim << std::endl;
    std::cout << "Average BH execution time for theta = 0.7: " << totTime07 / (double)num_sim << std::endl;
    std::cout << "Average BH execution time for theta = 1.0: " << totTime10 / (double)num_sim << std::endl;

    std::cout << "Average speed up with theta = 0.5: " << averageSpeedUp05 / (double)num_sim << std::endl;
    std::cout << "Average speed up with theta = 0.7: " << averageSpeedUp07 / (double)num_sim << std::endl;
    std::cout << "Average speed up with theta = 1.0: " << averageSpeedUp10 / (double)num_sim << std::endl;
    return 0;
}
