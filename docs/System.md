## Particle class
Represent a system of particles.
```c++
/*
*   Initialize System with Barnes Hut parameters
*/
System(std::function<void(Particle &, Particle &)> func, T discretizer, double deltaTime, 
       std::vector<double> max, std::vector<double> min);

/*
*   Initialize System with standard Barnes Hut parameters
*/
System(std::function<void(Particle &, Particle &)> func, T discretizer,
       double deltaTime);

/*
*   Compute a time step using "standard" method
*/
void compute();

/*
*   Compute a time step using MPI
*/
void computeMPI();

/*
*   Compute a time step using Barnes Hut
*/
void computeBH();

/*
*   Add a particle to the system
*/
void addParticle(Particle particle);

/*
*   Print all particles in the system
*/
void printParticles() const;

/*
*   Get reference to a particle in the system
*/
const Particle &getParticle(int index) const;

/*
*   Get reference to a vector containing all particles of the system
*/
const std::vector<Particle> &getParticles() const { return _systemParticles; }
```

## Note 
The actual available discretizers are:
- ```NBodyEnv::EulerDiscretizer```
- ```NBodyEnv::RKDiscretizer```
- ```NBodyEnv::VerletDiscretizer```

You can read more about discretizer in [Discretizers](Discretizers.md)