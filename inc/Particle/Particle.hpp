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
    double getDistance(Pos pos);
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
#if defined(_OPENMP)
#pragma omp atomic
#endif // _OPENMP
      xForce -= 2 * xForce;
#if defined(_OPENMP)
#pragma omp atomic
#endif // _OPENMP
      yForce -= 2 * yForce;
#if defined(_OPENMP)
#pragma omp atomic
#endif // _OPENMP
      zForce -= 2 * zForce;
    }
  };

  class Particle
  {
  public:
    Particle(ParticleType type, Pos pos, Vel vel, double specInfo, double radius)
        : _type(type), _pos(pos), _vel(vel), _force({0, 0, 0}),
          _specInfo(specInfo), _radius(radius), _visible(true){};

    // GETTERS
    const Pos &getPos() const { return _pos; }
    const Vel &getVel() const { return _vel; }
    const Force &getForce() const { return _force; }
    const double &getRadius() const { return _radius; }
    const ParticleType &getType() const { return _type; }
    const double &getSpecInfo() const { return _specInfo; }
    const bool &getVisible() const { return _visible; }

    // SETTERS
    void setPos(Pos pos) { _pos = pos; }
    void setVel(Vel vel) { _vel = vel; }
    void setRadius(double radius) { _radius = radius; }
    void setSpecInfo(double specInfo) { _specInfo = specInfo; }
    void setForce(Force force) { _force = force; }
    void setVisible(bool visible) { _visible = visible; }

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
#if defined(_OPENMP)
#pragma omp atomic
#endif // _OPENMP
      _force.xForce += force.xForce;
#if defined(_OPENMP)
#pragma omp atomic
#endif // _OPENMP
      _force.yForce += force.yForce;
#if defined(_OPENMP)
#pragma omp atomic
#endif // _OPENMP
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

    // Invert all x
    void invertX()
    {
      _force.xForce = -_force.xForce;
      _vel.xVel = -_vel.xVel;
    }

    // Invert all y
    void invertY()
    {
      _force.yForce = -_force.yForce;
      _vel.xVel = -_vel.xVel;
    }

    // Invert all z
    void invertZ()
    {
      _force.zForce = -_force.zForce;
      _vel.zVel = -_vel.zVel;
    }

    ~Particle() = default;

  protected:
    ParticleType _type;
    Pos _pos;
    Vel _vel;
    Force _force;
    double _specInfo;
    double _radius;
    // boolean flag to check if particle had a previous collision
    // if false, it will be ignored in the following calculations
    // and will be teleported outside of the domain so that it doesn't appear in
    // the plot
    bool _visible;
  };
} // namespace NBodyEnv

#endif
