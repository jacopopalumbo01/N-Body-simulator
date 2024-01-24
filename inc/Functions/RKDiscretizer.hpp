#ifndef RKDISCRETIZER
#define RKDISCRETIZER

#include <vector>
#include <Particle/Particle.hpp>
#include <Functions/Functions.hpp>

// Explicit
#define DISC_FEULER 1

// Implicit
#define DISC_BEULER 2

namespace NBodyEnv {
    class RKDiscretizer 
    {
        public:
            RKDiscretizer(int type){
                switch(type){
                    case DISC_FEULER:
                        setFeuler();
                        break;
                    case DISC_BEULER:
                        setBeuler();
                    default:
                        setFeuler();
                        break;
                }
            }

            // Discretize 
            void discretize(Particle &target, Particle &particleOne, Particle &particleTwo, std::function<Force(Pos &, Pos &, double, double, double, double)> func, double deltaTime);

        private:
            std::vector<std::vector<double>> m_a;
            std::vector<double> m_b;
            std::vector<double> m_c;

            Vel discretizeVel(Particle &, Particle &, std::function<Force(Pos &, Pos &, double, double, double, double)>, double);

            // Clear all vectors
            void clear();
            // Discretizer
            void setFeuler();
            void setBeuler();
    };
}

#endif