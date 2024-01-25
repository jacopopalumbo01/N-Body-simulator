## Particle class
Represent a particle in 3d space.
```c++
NBodyEnv::Particle();
NBodyEnv::Particle(ParticleType, Pos, Vel, double specInfo, double radius);

/*
*   Getters
*/
const Pos &getPos() const;
const Vel &getVel() const;
const Force &getForce() const; 
const double &getRadius() const; 
const ParticleType &getType() const; 
const double &getSpecInfo() const;
const bool &getVisible() const;

Pos getValuePos();
Vel getValueVel();

/*
*   Setters
*/
void setPos(Pos);
void setVel(Vel);
void setRadius(double);
void setSpecInfo(double);
void setForce(Force);
void setVisible(bool);

/*
*   Print particle infos
*/
void print() const;


```