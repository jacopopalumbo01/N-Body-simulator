#ifndef PARTICLE

#define PARTICLE

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
  };

  // ABSTRACT CLASS for generic particle
  class Particle
  {
  public:
    // TODO: may remove parameter type, since it's implicit in the derived class object that is being instantiated
    Particle(ParticleType type, Pos pos, Vel vel, double radius)
        // : _type(type), _specInfo(specInfo), _pos(pos), _vel(vel){};
        : _type(type), _pos(pos), _vel(vel), _radius(radius){};

    // GETTERS
    // declare abstract method to get the particle type
    virtual const ParticleType getType() const = 0;
    const Pos &getPos() const { return _pos; }
    const Vel &getVel() const { return _vel; }
    const Force &getForce() const { return _force; }
    const double &getRadius() const { return _radius; }
    // const ParticleType &getType() const { return _type; }
    // const double &getSpecInfo() const { return _specInfo; }

    // SETTERS
    void setPos(Pos pos) { _pos = pos; }
    void setVel(Vel vel) { _vel = vel; }
    void setForce(Force force) { _force = force; }
    // this shoudn't be necessary since the radius is set in the constructor
    // void setRadius(double radius) { _radius = radius; }

    // declare as pure virtual function, will be overriden by derived classes EMParticle and GravParticle
    // TODO: do the same for the type. Maybe even remove this and directly declare the analogous method
    // in the derived classes
    virtual const double &getSpecInfo() const = 0;

    virtual const Force &computeForce(const Particle &p2) const = 0;

    // method that inverts the components of the force
    void invertForce() 
    { 
      _force.xForce = -_force.xForce;
      _force.yForce = -_force.yForce;
      _force.zForce = -_force.zForce;
    }

    // virtual method to compute the generic force between two particles
    // problem since the force is different for different types of particles, while the parameter for the generic
    // force is the generic particle ==> signature of the method should change in the derived classes
    // virtual const double &computeForce(const Particle &p2) const = 0;

    virtual ~Particle() = default;

  private:
    ParticleType _type;
    Pos _pos;
    Vel _vel;
    Force _force;
    // double _specInfo;
    double _radius;
  };
} // namespace NBodyEnv

#endif // !DEBUG
