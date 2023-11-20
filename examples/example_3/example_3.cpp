#include <iostream>
#include <vector>

#include "../../src/Particle/Particle.hpp"
#include "../../src/Particle/EMParticle.hpp"
#include "../../src/Particle/GravParticle.hpp"

int main()
{
    NBodyEnv::GravParticle testGravParticle(NBodyEnv::gravitational,
                                            {1.0, 1.0, 1.0}, {1.0, 0.0, 0.0}, 1.2, 1e5);

    std::cout << "  Mass : " << testGravParticle.getSpecInfo() << " kg" << std::endl;
    std::cout << "  Position: {" << testGravParticle.getPos().xPos << ", "
              << testGravParticle.getPos().yPos << ", " << testGravParticle.getPos().zPos
              << "}" << std::endl;
    std::cout << "  Velocity: {" << testGravParticle.getVel().xVel << ", "
              << testGravParticle.getVel().yVel << ", " << testGravParticle.getVel().zVel
              << "}" << std::endl;

    // create another gravParticle
    NBodyEnv::GravParticle testGravParticle2(NBodyEnv::gravitational,
                                             {30.0, 30.0, 30.0}, {0.0, -1.0, 0.0}, 1.1, 1e5);

    std::cout << "  Mass : " << testGravParticle2.getSpecInfo() << " kg" << std::endl;
    std::cout << "  Position: {" << testGravParticle2.getPos().xPos << ", "
              << testGravParticle2.getPos().yPos << ", " << testGravParticle2.getPos().zPos
              << "}" << std::endl;
    std::cout << "  Velocity: {" << testGravParticle2.getVel().xVel << ", "
              << testGravParticle2.getVel().yVel << ", " << testGravParticle2.getVel().zVel
              << "}" << std::endl;

    // define time instant for the simulation
    constexpr double delta_time = 1.0;

    // declare vector to store the position of the particles
    std::vector<NBodyEnv::Pos> posParticle1;
    std::vector<NBodyEnv::Pos> posParticle2;

    // declare vector to store the velocity of the particles
    std::vector<NBodyEnv::Vel> velParticle1;
    std::vector<NBodyEnv::Vel> velParticle2;

    // now simulate the evolution of the system composed by the two particles over 100 time steps
    for (int i = 0; i < 10; i++)
    {
        // compute the force between the two particles
        testGravParticle.setForce(testGravParticle.computeForce(testGravParticle2));
        testGravParticle2.setForce(testGravParticle.getForce());
        testGravParticle2.invertForce();
    
        testGravParticle.setForce(testGravParticle.computeForce(testGravParticle2));
        std::cout << "  Force between the two particles: {" << testGravParticle.getForce().xForce << ", "
                << testGravParticle.getForce().yForce << ", " << testGravParticle.getForce().zForce
                << "}" << std::endl;

        // update the position of the particles based on the previous velocity
        testGravParticle.setPos({testGravParticle.getPos().xPos + testGravParticle.getVel().xVel * delta_time,
                                 testGravParticle.getPos().yPos + testGravParticle.getVel().yVel * delta_time,
                                 testGravParticle.getPos().zPos + testGravParticle.getVel().zVel * delta_time});

        testGravParticle2.setPos({testGravParticle2.getPos().xPos + testGravParticle2.getVel().xVel * delta_time,
                                  testGravParticle2.getPos().yPos + testGravParticle2.getVel().yVel * delta_time,
                                  testGravParticle2.getPos().zPos + testGravParticle2.getVel().zVel * delta_time});

        // store the position of the particles
        posParticle1.emplace_back(testGravParticle.getPos());
        posParticle2.emplace_back(testGravParticle2.getPos());

        // update the velocity of the particles based on the previous force
        testGravParticle.setVel({testGravParticle.getVel().xVel + testGravParticle.getForce().xForce * delta_time,
                                 testGravParticle.getVel().yVel + testGravParticle.getForce().yForce * delta_time,
                                 testGravParticle.getVel().zVel + testGravParticle.getForce().zForce * delta_time});

        testGravParticle2.setVel({testGravParticle2.getVel().xVel + testGravParticle2.getForce().xForce * delta_time,
                                  testGravParticle2.getVel().yVel + testGravParticle2.getForce().yForce * delta_time,
                                  testGravParticle2.getVel().zVel + testGravParticle2.getForce().zForce * delta_time});

        // store the velocity of the particles
        velParticle1.emplace_back(testGravParticle.getVel());
        velParticle2.emplace_back(testGravParticle2.getVel());
    }

    // compute the force between the two particles
    // testGravParticle.setForce(testGravParticle.computeForce(testGravParticle2));
    // std::cout << "  Force between the two particles: {" << testGravParticle.getForce().xForce << ", "
    //           << testGravParticle.getForce().yForce << ", " << testGravParticle.getForce().zForce
    //           << "}" << std::endl;

    // print the position of the particles in a loop using auto
    std::cout << "  Position of the first particle: " << std::endl;
    for (auto &pos : posParticle1)
    {
        std::cout << "  {" << pos.xPos << ", " << pos.yPos << ", " << pos.zPos << "}" << std::endl;
    }

    // same for the second particle
    std::cout << "  Position of the second particle: " << std::endl;
    for (auto &pos : posParticle2)
    {
        std::cout << "  {" << pos.xPos << ", " << pos.yPos << ", " << pos.zPos << "}" << std::endl;
    }

    // do the same for the velocity
    std::cout << "  Velocity of the first particle: " << std::endl;
    for (auto &vel : velParticle1)
    {
        std::cout << "  {" << vel.xVel << ", " << vel.yVel << ", " << vel.zVel << "}" << std::endl;
    }

    // same for the second particle
    std::cout << "  Velocity of the second particle: " << std::endl;
    for (auto &vel : velParticle2)
    {
        std::cout << "  {" << vel.xVel << ", " << vel.yVel << ", " << vel.zVel << "}" << std::endl;
    }

    return 0;
}
