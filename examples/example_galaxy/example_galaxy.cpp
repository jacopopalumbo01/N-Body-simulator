#include "Exporter/Exporter.hpp"
#include "Functions/EulerDiscretizer.hpp"
#include "Functions/Functions.hpp"
#include "Functions/VerletDiscretizer.hpp"
#include "Particle/Particle.hpp"
#include "Simulator/Simulator.hpp"
#include "System/System.hpp"
#include "TreeNode/TreeNode.hpp"
#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    // Open the file
    std::ifstream inputFile("stars.dat");
    double const kparsec = 3.085677581e19; 
    double const timeStep = 3e13;

    // Check if the file is open
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    const int numStars = 43802;

    // Vectors to store positions and velocities
    std::vector<double> xPositions(numStars);
    std::vector<double> yPositions(numStars);
    std::vector<double> zPositions(numStars);
    std::vector<double> vxVelocities(numStars);
    std::vector<double> vyVelocities(numStars);
    std::vector<double> vzVelocities(numStars);

    // Read data from the file
    for (int i = 0; i < numStars; ++i)
    {
        inputFile >> zPositions[i] >> yPositions[i] >> xPositions[i] >> vzVelocities[i] >> vyVelocities[i] >> vxVelocities[i];
    }

    // Close the file
    inputFile.close();

    // generate particles with such initial positions and velocities
    NBodyEnv::System<NBodyEnv::VerletDiscretizer> parallelSystem(NBodyEnv::Functions::getGravFunc(), NBodyEnv::VerletDiscretizer(), timeStep);
    for (int i = 0; i < numStars; ++i)
    {
        NBodyEnv::Particle particle(
            NBodyEnv::gravitational,
            {xPositions[i]*kparsec, yPositions[i]*kparsec, zPositions[i]*kparsec},
            {vxVelocities[i], vyVelocities[i], vzVelocities[i]}, 6.324e5, 40);
        parallelSystem.addParticle(particle);
    }

#if defined(_OPENMP)
    omp_set_num_threads(16);
#endif // _OPENMP

    const int numSim = 100;
    NBodyEnv::Exporter exporter("galaxy_test.part", timeStep);
    for (int i = 0; i < numSim; i++)
    {
        parallelSystem.compute();
        exporter.saveState(parallelSystem.getParticles());
    }

    exporter.close();

    return 0;
}
