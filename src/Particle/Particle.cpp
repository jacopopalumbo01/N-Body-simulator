#include "../../inc/Particle/Particle.hpp"
#include <cmath>
#include <iostream>

namespace NBodyEnv {

double Pos::getDistance(Pos pos) {
  double xDist = xPos - pos.xPos;
  double yDist = yPos - pos.yPos;
  double zDist = zPos - pos.zPos;
  double dist = std::sqrt(xDist * xDist + yDist * yDist + zDist * zDist);

  return dist;
}

void Particle::print() const {

  std::cout << "  Mass : " << _specInfo << " kg" << std::endl;
  std::cout << "  Position: {" << _pos.xPos << ", " << _pos.yPos << ", "
            << _pos.zPos << "}" << std::endl;
  std::cout << "  Velocity: {" << _vel.xVel << ", " << _vel.yVel << ", "
            << _vel.zVel << "}" << std::endl;
}
} // namespace NBodyEnv
