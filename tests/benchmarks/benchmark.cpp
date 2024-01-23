#include <N-Body-sim.hpp>
#include <benchmark/benchmark.h>
#include <cstdlib>

static void NGravParticlesVerletBenchmark(benchmark::State &state) {
  for (auto _ : state) {
    NBodyEnv::System testSystem(NBodyEnv::Functions::getGravFunc(),
                            NBodyEnv::VerletDiscretizer(), 1.0);

    // Create and add test particles
    for (int i = 0; i < state.range(0); i++) {
      NBodyEnv::Particle particle(
          NBodyEnv::gravitational,
          {rand() * 1000.00, rand() * 1000.00, rand() * 1000.00},
          {0.0, 0.0, 0.0}, rand() * 1.0e10, 50);
      testSystem.addParticle(particle);
    }
    // Create simulator
    NBodyEnv::Simulator<NBodyEnv::VerletDiscretizer> simulator(
        testSystem, (int)state.range(1));
    // Run simulation
    simulator.run();
  }
  state.SetComplexityN(state.range(1) * state.range(0) *
                       state.range(0)); /* O(M*N^2) */
}

static void NGravParticlesVerletExportBenchmark(benchmark::State &state) {
  for (auto _ : state) {
    NBodyEnv::System testSystem(NBodyEnv::Functions::getGravFunc(),
                                NBodyEnv::VerletDiscretizer(), 1.0);

    // Create and add test particles
    for (int i = 0; i < state.range(0); i++) {
      NBodyEnv::Particle particle(
          NBodyEnv::gravitational,
          {rand() * 1000.00, rand() * 1000.00, rand() * 1000.00},
          {0.0, 0.0, 0.0}, rand() * 1.0e10, 50);
      testSystem.addParticle(particle);
    }
    // Create exporter
    NBodyEnv::Exporter exporter("test.part", 1.0);

    // Create simulator
    NBodyEnv::Simulator<NBodyEnv::VerletDiscretizer> simulator(
        testSystem, &exporter, (int)state.range(1), 1);
    // Run simulation
    simulator.run();
  }

  state.SetComplexityN(state.range(1) * state.range(0) *
                       state.range(0)); /* O(M*N^2)*/
}

constexpr int simTime = 3600 * 24 * 7;

BENCHMARK(NGravParticlesVerletBenchmark)
    ->Args({2, simTime})
    ->Args({4, simTime})
    ->Args({8, simTime})
    ->Args({16, simTime})
    ->Complexity();

BENCHMARK(NGravParticlesVerletExportBenchmark)
    ->Args({2, simTime})
    ->Args({4, simTime})
    ->Args({8, simTime})
    ->Args({16, simTime})
    ->Complexity();

BENCHMARK_MAIN();
