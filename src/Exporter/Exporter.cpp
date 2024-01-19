#include "Exporter/Exporter.hpp"
#include <vector>

namespace NBodyEnv
{
  void Exporter::saveState(std::vector<Particle> particles)
  {
    // Declare time step
    _expFile << "---" << (double)_index * _deltaTime << "\n";

    // For each particle
    for (auto part = particles.begin(); part != particles.end(); part++)
    {
      // Get particle index
      int partInd = part - particles.begin();

      // Output particle positions
      _expFile << "PART" << partInd << " " << part->getPos().xPos << " "
               << part->getPos().yPos << " " << part->getPos().zPos << "\n";
      //     << " Force: " << part->getForce().xForce << " "
      //     << part->getForce().yForce << " " << part->getForce().zForce
      // _expFile  << " Vel: " << part->getVel().xVel << " " << part->getVel().yVel
      //   << " " << part->getVel().zVel << "\n";
    }

    // Increase index
    _index++;
  }
} // namespace NBodyEnv
