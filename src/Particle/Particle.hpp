#ifndef PARTICLE

#define PARTICLE

#include <functional>
namespace NBodyEnv {

// Defines the type of particle
enum ParticleType { gravitational, em };

struct Pos {
  double xPos;
  double yPos;
  double zPos;
};

struct Vel {
  double xVel;
  double yVel;
  double zVel;
};

struct Force {
  double xForce;
  double yForce;
  double zForce;
  // Invert force
  void invert() {
    xForce = -xForce;
    yForce = -yForce;
    zForce = -zForce;
  }
};

// ABSTRACT CLASS for generic particle
class Particle {
public:
  Particle(ParticleType type, ParticleType specInfo, Pos pos, Vel vel,
           double radius)
      : _type(type), _specInfo(specInfo), _pos(pos), _vel(vel),
        _radius(radius){};

  // GETTERS
  const Pos &getPos() const { return _pos; }
  const Vel &getVel() const { return _vel; }
  const Force &getForce() const { return _force; }
  const double &getRadius() const { return _radius; }
  const ParticleType &getType() const { return _type; }
  const double &getSpecInfo() const { return _specInfo; }

  // SETTERS
  void setPos(Pos pos) { _pos = pos; }
  void setVel(Vel vel) { _vel = vel; }
  void setForce(Force force) { _force = force; }

  // Compute the force between Particle and another particle. The std::function
  // func modifies forcess of both particles.
  void computeForce(Particle &p2,
                    const std::function<void(Particle &, Particle &)> &func) {
    func(*this, p2);
  }

  // Add new force contribution
  void addForce(const Force &force) {
    _force.xForce += force.xForce;
    _force.yForce += force.yForce;
    _force.zForce += force.zForce;
  }

  ~Particle() = default;

private:
  ParticleType _type;
  Pos _pos;
  Vel _vel;
  Force _force;
  double _specInfo;
  double _radius;
};
} // namespace NBodyEnv

#endif
