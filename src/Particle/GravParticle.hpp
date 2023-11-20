#ifndef GRAVPARTICLE

#define GRAVPARTICLE

#include "Particle.hpp"

namespace NBodyEnv
{

    class GravParticle : public Particle
    {
    public:
        GravParticle(ParticleType type, Pos pos, Vel vel, double radius, double mass)
            : Particle(type, pos, vel, radius), _mass(mass) {};

        // override the specInfo getter
        const double &getSpecInfo() const override { return _mass; }
        const ParticleType getType() const override { return ParticleType::gravitational; }

        // setter for the mass
        void setMass(double mass) { _mass = mass; }

        // method to compute the gravitational force between two particles
        // override base class method to compute the force
        // TODO: should update the force attribute of the particle, so that we keep track of all the global interactions (otherwise passing by non const reference is useless)
        const Force &computeForce(const Particle &p2) const override;

        // override destructor
        ~GravParticle() override = default;

    private:
        double _mass;
    };
}; // namespace NBodyEnv

#endif // !DEBUG