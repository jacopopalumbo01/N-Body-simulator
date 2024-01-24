#include "Parser.hpp"

int main(int argc, char** argv) {
    std::vector<std::vector<Vec>> particles_;
    std::vector<double> time_steps_;
	size_t iter_;
    Parser parser = Parser("test.part", 1.0);
    particles_ = parser.getParticles();
    time_steps_ = parser.getTime();
    iter_ = 0;

    std::cout << "Number of particles: " << particles_[0].size() << std::endl;
    std::cout << "Number of time steps: " << time_steps_.size() << std::endl;
    for(int i = 0; i < particles_[0].size(); ++i) 
    {
        std::cout << "Particle " << i+1 << " in position: " << particles_[0].at(i).x << " " << particles_[0].at(i).x << " " << particles_[0].at(i).x << std::endl;
     }

    return 0;
}