#ifndef SIMULATOR
#define SIMULATOR

#include "../Exporter/Exporter.hpp"
#include "../Functions/VerletDiscretizer.hpp"
#include "../System/System.hpp"
#include <functional>

namespace NBodyEnv {
template <class T> class Simulator {
public:
  Simulator(NBodyEnv::System<T> &sys, int numSteps)
      : m_numSteps(numSteps), m_numExp(0), m_system(sys) {}

  Simulator(NBodyEnv::System<T> &sys, NBodyEnv::Exporter *exp, int numSteps,
            int numExp)
      : m_export(true), m_numSteps(numSteps), m_numExp(numExp), m_exporter(exp),
        m_system(sys) {}

  void run() {
    if (!m_export) {
      for (int i = 0; i < m_numSteps; i++) {
        m_system.compute();
      }
    } else {

      for (int i = 0; i < m_numSteps; i++) {
        m_system.compute();
        if (i % m_numExp == 0) {
          m_exporter->saveState(m_system.getParticles());
        }
      }
    }
  }

private:
  bool m_export = false;
  int m_numSteps;
  int m_numExp;
  NBodyEnv::Exporter *m_exporter = nullptr;
  NBodyEnv::System<T> m_system;
};
} // namespace NBodyEnv
#endif
