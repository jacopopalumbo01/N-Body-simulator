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
    NBodyEnv::System testSystem(NBodyEnv::Functions::getGravFunc(), 1.0);

    // create Sun - Earth - Moon system with real values and simulate it
    NBodyEnv::Particle particleSun(NBodyEnv::gravitational, {0.0, 0.0, 0.0},
                                   {0.0, 0.0, 0.0}, 3.955e30, 6.96e5);
    NBodyEnv::Particle particleEarth(NBodyEnv::gravitational, {1.5e11, 0.0, 0.0},
                                     {0.0, 2.978e4, 0.0}, 5.972e24, 6.371e3);
    NBodyEnv::Particle particleMoon(NBodyEnv::gravitational, {1.5e11, 3.84e8, 0.0},
                                    {-3.683e3, 2.978e4, 0.0}, 7.3477e22, 1.737e3);

    testSystem.addParticle(particleSun);
    testSystem.addParticle(particleEarth);
    // testSystem.addParticle(particleMoon);

    // Create exporter
    NBodyEnv::Exporter exporter("test.part", 1.0);

    // simulate over a year time span
    for (int i = 0; i < 3600 * 24 * 7; i++)
    {
        testSystem.compute();
        if (i % 3600 == 0)
            exporter.saveState(testSystem.getParticles());
    }

    // print p1 mass
    std::cout << "Sun mass: " << testSystem.getParticle(0).getSpecInfo() << std::endl;
    // print p1 radius
    std::cout << "Sun radius: " << testSystem.getParticle(0).getRadius() << std::endl;

    exporter.close();

    return 0;
}
