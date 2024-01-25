#ifndef RKDISCRETIZER
#define RKDISCRETIZER

#include <vector>
#include <Particle/Particle.hpp>
#include <Functions/Functions.hpp>

// Explicit Euler
#define DISC_FEULER 1
// Explicir Midpoint
#define DISC_EXPMID 6
// Heun
#define DISC_HEUN 7
// Ralston
#define DISC_RALSTON 8
// Kutta 3
#define DISC_KUTTA3 9
// Heun 3
#define DISC_HEUN3 10
// Van der Houwen's/Wray third-order method
#define DISC_WRAY3 11
// Ralston's third-order method
#define DISC_RALSTON3 12
// Third-order Strong Stability Preserving Runge-Kutta
#define DISC_SSPRK3 13
// RK4
#define DISC_RK4 3
// RK38
#define DISC_RK38 14
// Ralston's fourth-order method
#define DISC_RALSTON4 15

// Implicit Euler
#define DISC_BEULER 2
// Implicit Midpoint
#define DISC_IMPMID 4
// Crank Nicolson
#define DISC_CRANKNIC 5

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
                    case DISC_RK4:
                        setRK4();
                    case DISC_IMPMID:
                        setImpMid();
                    case DISC_CRANKNIC:
                        setCrankNic();
                    case DISC_EXPMID:
                        setExpMid();
                    case DISC_HEUN:
                        setHeun();
                    case DISC_RALSTON:
                        setRalston();
                    case DISC_KUTTA3:
                        setKutta3();
                    case DISC_HEUN3:
                        setHeun3();
                    case DISC_WRAY3:
                        setWray3();
                    case DISC_RALSTON3:
                        setRalston3();
                    case DISC_SSPRK3:
                        setSSPRK3();
                    case DISC_RK38:
                        setRK38();
                    case DISC_RALSTON4:
                        setRalston4();
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
            void setRK4();
            void setImpMid();
            void setCrankNic();
            void setExpMid();
            void setHeun();
            void setRalston();
            void setKutta3();
            void setHeun3();
            void setWray3();
            void setRalston3();
            void setSSPRK3();
            void setRK38();
            void setRalston4();
    };
}

#endif