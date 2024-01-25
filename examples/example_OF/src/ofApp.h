#pragma once

#include "ofMain.h"
#include "Parser.hpp"
#include "ofxBloom.h"
#include <vector>

class ofApp : public ofBaseApp
{
private:
	std::vector<std::vector<Vec>> particles_;
    std::vector<double> time_steps_;
	size_t iter_;

	/* Camera utilities */
	ofEasyCam camera_;
	ofFbo fbo_;
	// std::shared_ptr<ofxBloom> bloom_;
	ofxBloom bloom_;
	size_t body_number;
	int scale_factor_;
	/*
	Will reset the simulation by clearing the bodies in the simulation and
	resetting the time passed.
  */
	void ResetSimulation();

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
};
