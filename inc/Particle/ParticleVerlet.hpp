#ifndef PARTICLEVERLET

#define PARTICLEVERLET

#include <functional>
#include "Particle.hpp"
#include <iostream>

namespace NBodyEnv {

struct Acc {
  double xAcc;
  double yAcc;
  double zAcc;
};

//Define the class for the verlet integration method
class ParticleVerlet : public Particle{
public:
  ParticleVerlet(ParticleType type, Pos pos, Vel vel, double specInfo, double radius, 
                Pos prevPartPos)
      : Particle(type, pos, vel, specInfo, radius),
        _vel_0(_vel),
        _acc({_force.xForce/_specInfo, _force.yForce/_specInfo, _force.zForce/_specInfo}), 
        _prevPartPos(prevPartPos){};


  // GETTERS
  const Acc &getAcc() const { return _acc; }
  const Pos &getPrevPart() const {return _prevPartPos; }

  // SETTERS
  void setAcc(Force force, double mass) {
    _acc.xAcc = force.xForce/mass;
    _acc.yAcc = force.yForce/mass;
    _acc.zAcc = force.zForce/mass;
  }
  void setPrevPart(Pos prevPartPos) {
    _prevPartPos = prevPartPos;
  }

  // Automatically update position
  void updatePos(double deltaTime) {
    Pos newPos = {2 * _pos.xPos - _prevPartPos.xPos + _acc.xAcc * deltaTime * deltaTime,
                  2 * _pos.yPos - _prevPartPos.yPos + _acc.yAcc * deltaTime * deltaTime,
                  2 * _pos.zPos - _prevPartPos.zPos + _acc.zAcc * deltaTime * deltaTime,
                  };
    setPrevPart(_pos);
    setPos(newPos);    
  }

  void updateFirstPos(double deltaTime) {
    setPrevPart(_pos);
    Pos idle = {_pos.xPos + _vel_0.xVel * deltaTime + (_acc.xAcc*deltaTime*deltaTime)/2,
            _pos.yPos + _vel_0.yVel * deltaTime + (_acc.yAcc*deltaTime*deltaTime)/2,
            _pos.zPos + _vel_0.zVel * deltaTime + (_acc.zAcc*deltaTime*deltaTime)/2       
            };
    setPos(idle);
  }

  void updateAcc() {
    setAcc(_force, _specInfo);
  }

   void computeForce(ParticleVerlet &p2,
                    const std::function<void(ParticleVerlet &, ParticleVerlet &)> &func) {
    func(*this, p2);
  }

  // Print particle infos
  void print() const;

  ~ParticleVerlet() = default;

protected:
  Vel _vel_0;
  Acc _acc;
  Pos _prevPartPos;
};
} // namespace NBodyEnv

#endif
