#include "../../inc/Exporter/Exporter.hpp"
#include "../../inc/Functions/Functions.hpp"
#include "../../inc/Particle/Particle.hpp"
#include "../../inc/System/System.hpp"
#include "../../inc/Collisions/Collisions.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    // create a new ParticleSystem by passing the function which computes the gravitational force
    // and the time step used for the simulation over time
    // NBodyEnv::System testSystem(NBodyEnv::Functions::getGravFunc(), 1);
    NBodyEnv::System testSystem(NBodyEnv::Functions::getGravFuncVerlet(), 1);

    // NBodyEnv::Particle particleOne(NBodyEnv::gravitational, {-500.0, 0.0, 0.0},
    //                                {0.0, 5e-3, 0.0}, 1.0e10, 10);
    // NBodyEnv::Particle particleTwo(NBodyEnv::gravitational, {500.0, 0.0, 0.0},
    //                                {0.0, -5e-3, 0.0}, 1.0e10, 10);
    // NBodyEnv::Particle particleThree(NBodyEnv::gravitational, {0.0, 0.0, 0.0},
    //                                  {0.0, 0.0, 0.0}, 1.0e10, 10);

    NBodyEnv::ParticleVerlet particleOne(NBodyEnv::gravitational, {-500.0, 0.0, 0.0},
                                         {0.0, 5e-3, 0.0}, 1.0e10, 10, {0.0, 0.0, 0.0});

    NBodyEnv::ParticleVerlet particleTwo(NBodyEnv::gravitational, {500.0, 0.0, 0.0},
                                         {0.0, -5e-3, 0.0}, 1.0e10, 10, {0.0, 0.0, 0.0});

    NBodyEnv::ParticleVerlet particleThree(NBodyEnv::gravitational, {0.0, 0.0, 0.0},
                                           {0.0, 0.0, 0.0}, 1.0e10, 10, {0.0, 0.0, 0.0});

    NBodyEnv::ParticleVerlet particleFour(NBodyEnv::gravitational, {1800.0, 100.0, 0.0},
                                           {1.0e-3, -4.0e-3, 0.0}, 1.0e10, 10, {0.0, 0.0, 0.0});

    NBodyEnv::ParticleVerlet particleFive(NBodyEnv::gravitational, {1200.0, -700.0, 0.0},
                                           {-2.0e-3, -1.0e-3, 0.0}, 1.0e10, 10, {0.0, 0.0, 0.0});

    NBodyEnv::ParticleVerlet particleSix(NBodyEnv::gravitational, {400.0, -900.0, 0.0},
                                           {-6.0e-3, 6.0e-3, 0.0}, 1.0e10, 10, {0.0, 0.0, 0.0});

    testSystem.addParticle(particleOne);
    testSystem.addParticle(particleTwo);
    testSystem.addParticle(particleThree);
    testSystem.addParticle(particleFour);
    testSystem.addParticle(particleFive);
    testSystem.addParticle(particleSix);

    // Create exporter
    NBodyEnv::Exporter exporter("../../../graphics/test.part", 1);

    // simulate over a year time span
    for (int i = 0; i < 3600 * 24 * 7; i++)
    {
        testSystem.computeVerlet();
        if (i % 3600 == 0)
            exporter.saveState(testSystem.getParticlesVerlet());
    }

    exporter.close();

    return 0;
}
