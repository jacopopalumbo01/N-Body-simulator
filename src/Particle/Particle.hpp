#ifndef PARTICLE

#define PARTICLE

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

class Particle {
public:
  Particle(ParticleType type, double specInfo, Pos pos, Vel vel)
      : _type(type), _specInfo(specInfo), _pos(pos), _vel(vel){};
  const Pos &getPos() const { return _pos; }
  const Vel &getVel() const { return _vel; }
  const ParticleType &getType() const { return _type; }
  const double &getSpecInfo() const { return _specInfo; }

private:
  Pos _pos;
  Vel _vel;
  ParticleType _type;
  double _specInfo;
};
} // namespace NBodyEnv

#endif // !DEBUG
