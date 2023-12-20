#include "../../inc/Exporter/Exporter.hpp"
#include "../../inc/Functions/EulerDiscretizer.hpp"
#include "../../inc/Functions/Functions.hpp"
#include "../../inc/Functions/VerletDiscretizer.hpp"
#include "../../inc/Particle/Particle.hpp"
#include "../../inc/System/System.hpp"
#include <benchmark/benchmark.h>
#include <cstdlib>

static void NGravParticlesEulerBenchmark(benchmark::State &state) {
  for (auto _ : state) {
    NBodyEnv::System System(NBodyEnv::Functions::getGravFunc(),
                                NBodyEnv::VerletDiscretizer(), 1.0);

    // Create and add test particles
    for (int i = 0; i < state.range(0); i++) {
      NBodyEnv::Particle particle(
          NBodyEnv::gravitational,
          {rand() * 1000.00, rand() * 1000.00, rand() * 1000.00},
          {0.0, 0.0, 0.0}, rand() * 1.0e10, 50);
      System.addParticle(particle);
    }

    for (int i = 0; i < 3600 * 24 * 7; i++) {
      System.compute();
    }
  }
}

BENCHMARK(NGravParticlesEulerBenchmark)
    ->RangeMultiplier(2)
    ->Range(2, 16)
    ->Complexity();

BENCHMARK_MAIN();
