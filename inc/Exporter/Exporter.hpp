#ifndef EXPORTER
#define EXPORTER

#include "../Particle/Particle.hpp"
#include "../Particle/ParticleVerlet.hpp"
#include <fstream>
#include <iostream>
#include <vector>

namespace NBodyEnv {
class Exporter {
public:
  Exporter(std::string path, double deltaTime) {
    _deltaTime = deltaTime;
    _index = 0;
    _expFile.open(path);
  }
  void saveState(std::vector<NBodyEnv::Particle>);
  void saveState(std::vector<NBodyEnv::ParticleVerlet>);
  void close() { _expFile.close(); }

private:
  std::ofstream _expFile;
  int _index;
  double _deltaTime;
};
} // namespace NBodyEnv
#endif
