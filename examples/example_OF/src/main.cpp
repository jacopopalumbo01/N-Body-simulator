#include "ofApp.h"

//========================================================================
int main()
{
    std::vector<std::vector<Vec>> particles;
    std::vector<double> time_steps;

    Parser parser = Parser("test.part", 1.0);
    particles = parser.getParticles();
    time_steps = parser.getTime();

    ofSetupOpenGL(3840, 2160, OF_WINDOW);
    ofRunApp(new ofApp());
}
