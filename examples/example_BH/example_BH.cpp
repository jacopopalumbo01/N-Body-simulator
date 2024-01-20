#include "Exporter/Exporter.hpp"
#include "Functions/EulerDiscretizer.hpp"
#include "Functions/Functions.hpp"
#include "Functions/VerletDiscretizer.hpp"
#include "Particle/Particle.hpp"
#include "Simulator/Simulator.hpp"
#include "System/System.hpp"
#include "TreeNode/TreeNode.hpp"
#include <iostream>

int main(int argc, char *argv[]) {

  NBodyEnv::System testSystem(NBodyEnv::Functions::getGravFunc(),
                              NBodyEnv::VerletDiscretizer(), 1.0);

  // BEAR IN MIND THAT PARTICLES SHOULD NOT BE INSERTED IN THE SAME EXACT POSITION
  // we currently do not handle this case, but when generating particles randomly this is
  // virtually impossible
  NBodyEnv::Particle particleOne(NBodyEnv::gravitational, {200.0, 200.0, 100.0},
                                 {5e-3, 0.0, 0.0}, 1.0e10, 50);
  NBodyEnv::Particle particleTwo(NBodyEnv::gravitational, {100.0, -1000.0, 100.0},
                                 {-5e-3, 0.0, 0.0}, 1.0e10, 50);
  NBodyEnv::Particle particleThree(NBodyEnv::gravitational, {-100.0, -1000.0, -100.0},
                                 {-5e-3, 0.0, 0.0}, 1.0e10, 50);
  NBodyEnv::Particle particleFour(NBodyEnv::gravitational, {100.0, -1000.0, -100.0},
                                 {-5e-3, 0.0, 0.0}, 1.0e10, 50);
  NBodyEnv::Particle particleFive(NBodyEnv::gravitational, {6000.0, -1000.0, -100.0},
                                 {-5e-3, 0.0, 0.0}, 1.0e10, 50);
  
  testSystem.addParticle(particleOne);
  testSystem.addParticle(particleTwo);

  NBodyEnv::TreeNode *root(new NBodyEnv::TreeNode(
      {10000.0, 10000.0, 10000.0}, {-10000.0, -10000.0, -10000.0}, nullptr));

  std::cout << "Inserting particle one" << std::endl;
  root->InsertParticle(particleOne,0);
  std::cout << "Inserting particle two" << std::endl;
  root->InsertParticle(particleTwo,0);
  std::cout << "Inserting particle three" << std::endl;
  root->InsertParticle(particleThree,0);
  std::cout << "Inserting particle four" << std::endl;
  root->InsertParticle(particleFour,0);
  std::cout << "Inserting particle five" << std::endl;
  root->InsertParticle(particleFive,0);

  std::cout << "\n";
  std::cout << "\n";
  std::cout << "Tot number of particles: " << root->GetNParticles() << std::endl;
  root->ComputeMass();
  // root->PrintMass();
  root->GetOctant(100.0, -1000.0, 100.0);

  // Create exporter
  // NBodyEnv::Exporter exporter("test.part", 1.0);

  // // Create Simulator
  // NBodyEnv::Simulator<NBodyEnv::VerletDiscretizer> simulator(
  //     testSystem, &exporter, 1000, 10);
  // simulator.run();

  // exporter.close();

  return 0;
}
