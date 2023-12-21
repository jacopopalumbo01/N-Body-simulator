#ifndef EXPORTER
#define EXPORTER

#include "../Particle/Particle.hpp"
#include <fstream>
#include <iostream>
#include <vector>

// class used to create an object that writes to a file the particle positions
// over time, in order to be able to visualize the simulation
namespace NBodyEnv {
class Exporter {
public:
  Exporter(std::string path, double deltaTime) {
    _deltaTime = deltaTime;
    _index = 0;
    _expFile.open(path);
  }
  void saveState(std::vector<NBodyEnv::Particle>);
  void close() { _expFile.close(); }
  ~Exporter() = default;

private:
  std::ofstream _expFile;
  int _index;
  double _deltaTime;
};
} // namespace NBodyEnv
#endif
