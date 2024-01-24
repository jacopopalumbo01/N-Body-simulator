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

int main() {
    // Open the file
    std::ifstream inputFile("1024part");

    // Check if the file is open
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    const int numStars = 1024;

    // Vectors to store positions, velocities, and mass
    std::vector<double> masses(numStars);
    std::vector<double> xPositions(numStars);
    std::vector<double> yPositions(numStars);
    std::vector<double> zPositions(numStars);
    std::vector<double> vxVelocities(numStars);
    std::vector<double> vyVelocities(numStars);
    std::vector<double> vzVelocities(numStars);

    // Read data from the file
    for (int i = 0; i < numStars; ++i) {
        inputFile >> masses[i] >> zPositions[i] >> yPositions[i] >> xPositions[i] >> vzVelocities[i] >> vyVelocities[i] >> vxVelocities[i];
    }

    // Close the file
    inputFile.close();

    // Now you can use the vectors masses, xPositions, yPositions, zPositions, vxVelocities, vyVelocities, vzVelocities

    // Example: Print the first mass and position
    std::cout << "First mass: " << masses[0] << std::endl;
    std::cout << "First position: (" << xPositions[0] << ", " << yPositions[0] << ", " << zPositions[0] << ")" << std::endl;

    // generate particles with such initial positions and velocities
    NBodyEnv::System<NBodyEnv::VerletDiscretizer> parallelSystem(NBodyEnv::Functions::getGravFunc(), NBodyEnv::VerletDiscretizer(), 30);
    for (int i = 0; i < numStars; ++i)
    {
        NBodyEnv::Particle particle(
            NBodyEnv::gravitational,
            {xPositions[i], yPositions[i], zPositions[i]},
            {vxVelocities[i], vyVelocities[i], vzVelocities[i]}, 6.324e5, 40);
        parallelSystem.addParticle(particle);
    }

#if defined(_OPENMP)
    omp_set_num_threads(12);
#endif // _OPENMP

    const int timeSteps = 360;
    NBodyEnv::Exporter exporter("star_cluster.part", 30);
    for (int i = 0; i < timeSteps; i++)
    {
        parallelSystem.compute();
        exporter.saveState(parallelSystem.getParticles());
    }

    exporter.close();

    return 0;
}
