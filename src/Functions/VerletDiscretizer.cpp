#include "Functions/Functions.hpp"
#include "Functions/VerletDiscretizer.hpp"
#include "Collisions/Collisions.hpp"
#include <iostream>
#include <math.h>
#include <omp.h>

namespace NBodyEnv {

void VerletDiscretizer::updatePos(Particle &p, Particle &prevP, double deltaTime){
    p.setPos({2 * p.getPos().xPos - prevP.getPos().xPos + p.getForce().xForce/p.getSpecInfo() * deltaTime * deltaTime,
              2 * p.getPos().yPos - prevP.getPos().yPos + p.getForce().yForce/p.getSpecInfo() * deltaTime * deltaTime,
              2 * p.getPos().zPos - prevP.getPos().zPos + p.getForce().zForce/p.getSpecInfo() * deltaTime * deltaTime
              });   
}

void VerletDiscretizer::updateFirsePos(Particle &p, double deltaTime){
    p.setPos({p.getPos().xPos + p.getVel().xVel * deltaTime + (p.getForce().xForce/p.getSpecInfo()*deltaTime*deltaTime)/2,
              p.getPos().yPos + p.getVel().yVel * deltaTime + (p.getForce().yForce/p.getSpecInfo()*deltaTime*deltaTime)/2,
              p.getPos().zPos + p.getVel().zVel * deltaTime + (p.getForce().zForce/p.getSpecInfo()*deltaTime*deltaTime)/2       
              });
}

} // namespace NBodyEnv
