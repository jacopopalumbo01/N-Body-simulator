#ifndef COLLISIONS
#define COLLISIONS

#include "../Particle/Particle.hpp"
#include <functional>

namespace NBodyEnv
{
    class Collisions
    {
    public:
        static void elasticCollision(Particle &p1, Particle &p2);
        static void inelasticCollision(Particle &p1, Particle &p2);
        static std::function<void(Particle &, Particle &)> getElasticCollision()
        {
            return elasticCollision;
        }
        static std::function<void(Particle &, Particle &)> getInelasticCollision()
        {
            return inelasticCollision;
        }
    };
} // namespace NBodyEnv

#endif