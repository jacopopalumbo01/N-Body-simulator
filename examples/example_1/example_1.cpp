#include <iostream>

#include "../../inc/Particle/Particle.hpp"

int main() {
  NBodyEnv::Particle testParticle(NBodyEnv::gravitational, 1e10,
                                  {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0});

  std::cout << "Example1 - Particle creation" << std::endl;

  if (testParticle.getType() == 0) {
    std::cout << "  Particle type: Gravitational" << std::endl;
  } else {
    std::cout << "  Particle type: Electromagnetic" << std::endl;
  }

  std::cout << "  Spec info: " << testParticle.getSpecInfo() << std::endl;
  std::cout << "  Position: {" << testParticle.getPos().xPos << ", "
            << testParticle.getPos().yPos << ", " << testParticle.getPos().zPos
            << "}" << std::endl;
  std::cout << "  Velocity: {" << testParticle.getVel().xVel << ", "
            << testParticle.getVel().yVel << ", " << testParticle.getVel().zVel
            << "}" << std::endl;

  return 0;
}
