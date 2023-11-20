#ifndef EMPARTICLE

#define EMPARTICLE

#include "Particle.hpp"

namespace NBodyEnv
{

    class EMParticle : public Particle
    {
    public:
        EMParticle(ParticleType type, Pos pos, Vel vel, double radius, double charge)
            : Particle(type, pos, vel, radius), _charge(charge){};

        // override the specInfo getter
        const double &getSpecInfo() const override { return _charge; }
        const ParticleType getType() const override { return ParticleType::em; }

        // setter for the charge
        void setCharge(double charge) { _charge = charge; }

        // method to compute the electromagnetic force between two particles
        const Force &computeForce(const Particle &p2) const override;

        // override destructor
        ~EMParticle() override = default;

    private:
        double _charge;
    };
}; // namespace NBodyEnv

#endif // !DEBUG
