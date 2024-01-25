#include "ofApp.h"

//========================================================================
int main()
{
    std::vector<std::vector<Vec>> particles;
    std::vector<double> time_steps;

    Parser parser = Parser("test.part", 1.0);
    particles = parser.getParticles();
    time_steps = parser.getTime();
    // // Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
    // ofGLWindowSettings settings;
    // settings.setSize(1024, 768);
    // settings.windowMode = OF_WINDOW; // can also be OF_FULLSCREEN

    // auto window = ofCreateWindow(settings);

    // ofRunApp(window, make_shared<ofApp>());
    // ofRunMainLoop();

    ofSetupOpenGL(3840, 2160, OF_WINDOW);
    ofRunApp(new ofApp());
}
