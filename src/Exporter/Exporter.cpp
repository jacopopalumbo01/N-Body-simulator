#include "Exporter.hpp"
#include <vector>

namespace NBodyEnv {
void Exporter::saveState(std::vector<Particle> particles) {
  // Declare time step
  _expFile << "---" << (double)_index * _deltaTime << "\n";

  // For each particle
  for (auto part = particles.begin(); part != particles.end(); part++) {
    // Get particle index
    int partInd = part - particles.begin();

    // Output particle positions
    _expFile << "PART" << partInd << " " << part->getPos().xPos << " "
             << part->getPos().yPos << " " << part->getPos().zPos << "\n";
  }

  // Increase index
  _index++;
}
} // namespace NBodyEnv
