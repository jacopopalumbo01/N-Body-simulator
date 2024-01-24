#include "Functions/RKDiscretizer.hpp"
#include <iostream>
namespace NBodyEnv{
    void RKDiscretizer::clear() {
        m_a.clear();
        m_b.clear();
        m_c.clear();
    }

    void RKDiscretizer::setFeuler() {
        clear();

        m_a.push_back({0.0});
        m_b.push_back(1.0);
        m_c.push_back(0.0);
    }

    void RKDiscretizer::setBeuler() {
        clear();

        m_a.push_back({1.0});
        m_b.push_back(1.0);
        m_c.push_back(1.0);
    }
    
    void RKDiscretizer::discretize(Particle &target, Particle &particleOne, Particle &particleTwo, std::function<Force(Pos &, Pos &, double, double, double, double)> func, double deltaTime){
        Pos tempPos;
        Pos particleTwoPos = particleTwo.getValuePos();
        Vel tempVel;
        Force force = {0.0, 0.0, 0.0};
        std::vector<Acc> k;
        Acc kSum;
        // Final vel
        Vel finalVel = {0.0, 0.0, 0.0};

        for(size_t i = 0; i < size(m_b); ++i) {

            // Reset tempPos value to original
            tempPos = particleOne.getValuePos();
            // Reset tempVel value to original
            tempVel = particleOne.getValueVel();

            // Update time
            double newT = m_c[i] * deltaTime;



            // Calculate sum of previous K
            kSum = {0.0, 0.0, 0.0};

            for(size_t j = 0; j < i; ++j) {
                kSum.xAcc += m_a[i][j] * k[j].xAcc;
                kSum.yAcc += m_a[i][j] * k[j].yAcc;
                kSum.zAcc += m_a[i][j] * k[j].zAcc;
            }

            // Compute new velocity
            tempVel.xVel += deltaTime * kSum.xAcc;
            tempVel.yVel += deltaTime * kSum.yAcc;
            tempVel.zVel += deltaTime * kSum.zAcc;

            // Update position
            tempPos.xPos += newT * tempVel.xVel;
            tempPos.yPos += newT * tempVel.yVel;
            tempPos.zPos += newT * tempVel.zVel;

            // Compute Force
            force = func(tempPos, particleTwoPos, particleOne.getSpecInfo(), particleTwo.getSpecInfo(), particleOne.getRadius(), particleTwo.getRadius());
            
            // Compute K (Acceleration)
            kSum.xAcc = force.xForce / particleOne.getSpecInfo();
            kSum.yAcc = force.yForce / particleOne.getSpecInfo();
            kSum.zAcc = force.zForce / particleOne.getSpecInfo();

            // Save k
            k.push_back(kSum);

            // Add contribute to final vel
            finalVel.xVel += deltaTime * m_b[i] * k[i].xAcc;
            finalVel.yVel += deltaTime * m_b[i] * k[i].yAcc;
            finalVel.zVel += deltaTime * m_b[i] * k[i].zAcc;
        }

        // Save computed velocity
        tempVel = {target.getVel().xVel, target.getVel().yVel, target.getVel().zVel};

        tempVel.xVel += finalVel.xVel;
        tempVel.yVel += finalVel.yVel;
        tempVel.zVel += finalVel.zVel;

        target.setVel(finalVel);

        // Compute new position
        tempPos = {target.getPos().xPos, target.getPos().yPos, target.getPos().zPos};
        tempPos.xPos += deltaTime * finalVel.xVel;
        tempPos.yPos += deltaTime * finalVel.yVel;
        tempPos.zPos += deltaTime * finalVel.zVel;

        // Save new position
        target.setPos(tempPos);
    }
}