#include "ofApp.h"
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(0, 0, 0);
    Parser parser = Parser("test.part", 1.0);
    particles_ = parser.getParticles();
    time_steps_ = parser.getTime();
    iter_ = 0;
    scale_factor_ = 1;

    ofDisableArbTex();
    fbo_.allocate(ofGetWidth(), ofGetHeight());
    ofEnableArbTex();
    bloom_.setup(ofGetWidth(), ofGetHeight(), fbo_);
}

//--------------------------------------------------------------
void ofApp::update()
{   
    if(iter_ == time_steps_.size() - 1)
        ResetSimulation();
    iter_++;
}

//--------------------------------------------------------------
void ofApp::draw()
{
    fbo_.begin();
    ofClear(0);
    camera_.begin();

    if (iter_ == 0)
    {
        Vec max = {0.0, 0.0, 0.0};
        Vec min = {0.0, 0.0, 0.0};
        for (Vec v : particles_[iter_])
        {
            if (v.x > max.x)
                max.x = v.x;
            if (v.y > max.y)
                max.y = v.y;
            if (v.z > max.z)
                max.z = v.z;
            if (v.x < min.x)
                min.x = v.x;
            if (v.y < min.y)
                min.y = v.y;
            if (v.x < min.x)
                min.y = v.y;
        }

        Vec fin = {0.0, 0.0, 0.0};
        if (max.x > -min.x)
            fin.x = max.x;
        else
            fin.x = -min.x;
        if (max.y > -min.y)
            fin.y = max.y;
        else
            fin.y = -min.y;
        if (max.z > -min.z)
            fin.z = max.z;
        else
            fin.z = -min.z;

        double absMax = 0.0;
        if (fin.x > fin.y && fin.x > fin.z)
            absMax = fin.x;
        else if (fin.y > fin.x && fin.y > fin.z)
            absMax = fin.y;
        else
            absMax = fin.z;

        while (absMax / scale_factor_ > ofGetHeight())
        {
            scale_factor_ *= 1.2;
        }
    }

    for (Vec v : particles_[iter_])
    {
        ofEnableAlphaBlending();
        // TODO: scale color with respect to mass / velocity
        ofSetColor(244, 107, 66);
        ofDrawSphere(v.x / (scale_factor_ * 17), v.y / (scale_factor_ * 17), v.z / (scale_factor_ * 17), 2);
    }

    camera_.end();

    fbo_.end();

    bloom_.setBrightness(2);
    bloom_.setScale(1);
    bloom_.setThreshold(.25);
    bloom_.process();
    bloom_.draw();

    ofSetColor(255, 255);

    ofDrawBitmapString("1 - Reset Simulation", 100, 100);

    string frame_rate = "Frame rate: " + ofToString(ofGetFrameRate(), 2);
    ofDrawBitmapString(frame_rate, 100, 135);

    string timeStep = "Time step: " + ofToString((time_steps_[iter_]));
    ofDrawBitmapString(timeStep, 100, 150);
}

void ofApp::ResetSimulation()
{
    particles_.clear();
    time_steps_.clear();
    Parser parser = Parser("test.part", 1.0);
    particles_ = parser.getParticles();
    time_steps_ = parser.getTime();
    iter_ = 0;
    scale_factor_ = 1;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key)
    {
    case '1':
        ResetSimulation();
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
