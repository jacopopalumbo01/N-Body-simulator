#ifndef PARTICLE
#define PARTICLE

#include <functional>
#include <omp.h>

namespace NBodyEnv
{

  // Defines the type of particle
  enum ParticleType
  {
    gravitational,
    em
  };

  struct Pos
  {
    double xPos;
    double yPos;
    double zPos;
  };

  struct Vel
  {
    double xVel;
    double yVel;
    double zVel;
  };

  struct Force
  {
    double xForce;
    double yForce;
    double zForce;
    // Invert force
    void invert()
    {
// xForce = -xForce;
// yForce = -yForce;
// zForce = -zForce;
#pragma omp atomic
      xForce -= 2 * xForce;
#pragma omp atomic
      yForce -= 2 * yForce;
#pragma omp atomic
      zForce -= 2 * zForce;
    }
  };

  // ABSTRACT CLASS for generic particle
  class Particle
  {
  public:
    Particle(ParticleType type, Pos pos, Vel vel, double specInfo, double radius)
        : _type(type), _pos(pos), _vel(vel), _force({0, 0, 0}),
          _specInfo(specInfo), _radius(radius){};

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
    void setRadius(double radius) { _radius = radius; }
    void setSpecInfo(double specInfo) { _specInfo = specInfo; }
    void setForce(Force force) { _force = force; }

    // Compute the force between Particle and another particle. The std::function
    // func modifies forcess of both particles.
    void computeForce(Particle &p2,
                      const std::function<void(Particle &, Particle &)> &func)
    {
      func(*this, p2);
    }

    // Add new force contribution
    void addForce(const Force &force)
    {
#pragma omp atomic
      _force.xForce += force.xForce;
#pragma omp atomic
      _force.yForce += force.yForce;
#pragma omp atomic
      _force.zForce += force.zForce;
    }

    // Automatically update position
    void updatePos(double deltaTime)
    {
      setPos({_pos.xPos + _vel.xVel * deltaTime,
              _pos.yPos + _vel.yVel * deltaTime,
              _pos.zPos + _vel.zVel * deltaTime});
    }

    // Automatically update velocity
    void updateVel(double deltaTime)
    {
      setVel({_vel.xVel + _force.xForce * deltaTime / _specInfo,
              _vel.yVel + _force.yForce * deltaTime / _specInfo,
              _vel.zVel + _force.zForce * deltaTime / _specInfo});
    }

    // Print particle infos
    void print() const;

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
