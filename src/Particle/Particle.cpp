#include "Particle.hpp"
#include <iostream>

namespace NBodyEnv {
void Particle::print() const {

  std::cout << "  Mass : " << _specInfo << " kg" << std::endl;
  std::cout << "  Position: {" << _pos.xPos << ", " << _pos.yPos << ", "
            << _pos.zPos << "}" << std::endl;
  std::cout << "  Velocity: {" << _vel.xVel << ", " << _vel.yVel << ", "
            << _vel.zVel << "}" << std::endl;
}
} // namespace NBodyEnv
