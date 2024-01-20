#include "Exporter/Exporter.hpp"
#include "Functions/EulerDiscretizer.hpp"
#include "Functions/Functions.hpp"
#include "Functions/VerletDiscretizer.hpp"
#include "Particle/Particle.hpp"
#include "Simulator/Simulator.hpp"
#include "System/System.hpp"
#include "TreeNode/TreeNode.hpp"
#include <iostream>

int main(int argc, char *argv[])
{

  NBodyEnv::System testSystem(NBodyEnv::Functions::getGravFunc(),
                              NBodyEnv::VerletDiscretizer(), 1.0);

  // BEAR IN MIND THAT PARTICLES SHOULD NOT BE INSERTED IN THE SAME EXACT POSITION
  // we currently do not handle this case, but when generating particles randomly this is
  // virtually impossible
  NBodyEnv::Particle particleOne(NBodyEnv::gravitational, {2000.0, 200.0, 100.0},
                                 {5e-3, 0.0, 0.0}, 1.0e10, 50);
  NBodyEnv::Particle particleTwo(NBodyEnv::gravitational, {2000.0, 200.0, 1000.0},
                                 {5e-3, 0.0, 0.0}, 1.0e10, 50);
  NBodyEnv::Particle particleThree(NBodyEnv::gravitational, {2000.0, 200.0, 1500.0},
                                   {5e-3, 0.0, 0.0}, 1.0e10, 50);
  NBodyEnv::Particle particleFour(NBodyEnv::gravitational, {2000.0, 200.0, 2500.0},
                                  {5e-3, 0.0, 0.0}, 1.0e10, 50);
  NBodyEnv::Particle particleFive(NBodyEnv::gravitational, {2000.0, 200.0, 7000.0},
                                  {5e-3, 0.0, 0.0}, 1.0e10, 50);
  NBodyEnv::Particle particleSix(NBodyEnv::gravitational, {8000.0, 1000.0, 6000.0},
                                 {-5e-3, 0.0, 0.0}, 1.0e10, 50);
  NBodyEnv::Particle particleSeven(NBodyEnv::gravitational, {-6000.0, -9000.0, -8000.0},
                                   {-5e-3, 0.0, 0.0}, 1.0e10, 50);

  testSystem.addParticle(particleOne);
  testSystem.addParticle(particleTwo);
  testSystem.addParticle(particleThree);
  testSystem.addParticle(particleFour);
  testSystem.addParticle(particleFive);
  testSystem.addParticle(particleSix);
  testSystem.addParticle(particleSeven);

  std::vector<double> max = {10000.0, 10000.0, 10000.0};
  std::vector<double> min = {-10000.0, -10000.0, -10000.0};

  NBodyEnv::TreeNode root(NBodyEnv::TreeNode(max, min, nullptr));

  root.ResetNode(max, min);

  root.InsertParticle(particleOne, 0);
  root.InsertParticle(particleTwo, 0);
  root.InsertParticle(particleThree, 0);
  root.InsertParticle(particleFour, 0);
  root.InsertParticle(particleFive, 0);
  root.InsertParticle(particleSix, 0);
  root.InsertParticle(particleSeven, 0);

  root.ComputeMass();

  // now compute force between particles in the test system
  for (int i = 0; i < root.GetNParticles(); ++i)
  {
    // std::cout << "Computing force for particle " << i << std::endl;
    std::vector<double> force = root.ComputeForce(testSystem.getParticle(i));
    // multiply components by 1e10 to get the force
    force[0] *= 1e10;
    force[1] *= 1e10;
    force[2] *= 1e10;
  }
  
  // Create exporter
  NBodyEnv::Exporter exporter("test.part", 1.0);

  // now compute force between particles in the test system
  testSystem.compute();
  // print force on p7
  std::cout << "Force on particle 7: " << testSystem.getParticle(6).getForce().xForce << " " << testSystem.getParticle(6).getForce().yForce << " " << testSystem.getParticle(6).getForce().zForce << std::endl;

  // // Create Simulator
  // NBodyEnv::Simulator<NBodyEnv::VerletDiscretizer> simulator(
  //     testSystem, &exporter, 1000, 10);
  // simulator.run();

  // exporter.close();

  return 0;
}
