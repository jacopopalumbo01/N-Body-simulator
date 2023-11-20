#include <iostream>

#include "../../src/Particle/Particle.hpp"
#include "../../src/Particle/EMParticle.hpp"
#include "../../src/Particle/GravParticle.hpp"

int main()
{
    NBodyEnv::GravParticle testGravParticle(NBodyEnv::gravitational,
                                            {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0}, 1.2, 1.0);

    if (testGravParticle.getType() == 0)
    {
        std::cout << "  Particle type: Gravitational" << std::endl;
    }
    else
    {
        std::cout << "  Particle type: Electromagnetic" << std::endl;
    }

    std::cout << "  Mass : " << testGravParticle.getSpecInfo() << " kg" << std::endl;
    std::cout << "  Position: {" << testGravParticle.getPos().xPos << ", "
              << testGravParticle.getPos().yPos << ", " << testGravParticle.getPos().zPos
              << "}" << std::endl;
    std::cout << "  Velocity: {" << testGravParticle.getVel().xVel << ", "
              << testGravParticle.getVel().yVel << ", " << testGravParticle.getVel().zVel
              << "}" << std::endl;

    // create another gravParticle
    NBodyEnv::GravParticle testGravParticle2(NBodyEnv::gravitational,
                                             {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, 1.1, 1.0);

    if (testGravParticle2.getType() == 0)
    {
        std::cout << "  Particle type: Gravitational" << std::endl;
    }
    else
    {
        std::cout << "  Particle type: Electromagnetic" << std::endl;
    }

    std::cout << "  Mass : " << testGravParticle2.getSpecInfo() << " kg" << std::endl;
    std::cout << "  Position: {" << testGravParticle2.getPos().xPos << ", "
              << testGravParticle2.getPos().yPos << ", " << testGravParticle2.getPos().zPos
              << "}" << std::endl;
    std::cout << "  Velocity: {" << testGravParticle2.getVel().xVel << ", "
              << testGravParticle2.getVel().yVel << ", " << testGravParticle2.getVel().zVel
              << "}" << std::endl;

    // compute the force between the two particles
    testGravParticle.setForce(testGravParticle.computeForce(testGravParticle2));
    testGravParticle2.setForce(testGravParticle.getForce());    
    testGravParticle2.invertForce();
    std::cout << "  Force between the two particles: {" << testGravParticle.getForce().xForce << ", "
              << testGravParticle.getForce().yForce << ", " << testGravParticle.getForce().zForce
              << "}" << std::endl;

    return 0;
}
