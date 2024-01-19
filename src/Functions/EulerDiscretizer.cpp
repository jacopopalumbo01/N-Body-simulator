#include "Functions/Functions.hpp"
#include "Functions/EulerDiscretizer.hpp"
#include "Collisions/Collisions.hpp"
#include <iostream>
#include <math.h>
#include <omp.h>

namespace NBodyEnv {
  
void EulerDiscretizer::discretize(Particle &p, double deltaTime) {
    p.updatePos(deltaTime);
    p.updateVel(deltaTime);
}
} // namespace NBodyEnv
