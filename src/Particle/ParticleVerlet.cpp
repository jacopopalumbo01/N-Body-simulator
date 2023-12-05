#include "../../inc/Particle/ParticleVerlet.hpp"
#include <iostream>

namespace NBodyEnv {
void ParticleVerlet::print() const {

  std::cout << "  Mass : " << _specInfo << " kg" << std::endl;
  std::cout << "  Position: {" << _pos.xPos << ", " << _pos.yPos << ", "
            << _pos.zPos << "}" << std::endl;
  std::cout << "  0_Velocity: {" << _vel_0.xVel << ", " << _vel_0.yVel << ", "
            << _vel_0.zVel << "}" << std::endl;
  std::cout << "  Acc: {" << _acc.xAcc << ", " << _acc.yAcc << ", "
            << _acc.zAcc << "}" << std::endl;
  std::cout << "  Force " << _force.xForce << ", " << _force.yForce << ", " << _force.zForce << std::endl;
}
} // namespace NBodyEnv
