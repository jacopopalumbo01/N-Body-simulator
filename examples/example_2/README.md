# EXAMPLE_2

Implementation of basic particle interaction. Spawn of two gravitational particles, which are objects of type GravParticle, a child class of the abstract class Particle. 
Computation of the gravitational force between the two particles at time t_0=0 with the ad hoc method `const Force &GravParticle::computeForce(const Particle &p2) const`. 
This method is declared virtual is the Particle class and overridden in all child classes, so that each particle 
cathegory implements its own interaction logic.  