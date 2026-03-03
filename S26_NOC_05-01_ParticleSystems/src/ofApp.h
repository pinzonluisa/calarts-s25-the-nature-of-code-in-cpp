//
//  ofApp.h
//  S25_NOC_06_ParticleSystem
//
//  Created by Luisa Pinzon
//
//  CLICK = move orbital center
//  SPACE = reset
//  F = fullscreen
//  H = hide GUI
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "emitter.hpp"
#include "attractor.hpp"

class ofApp : public ofBaseApp {

public:
    void setup() override;
    void update() override;
    void draw() override;
    
    void keyPressed(int key) override;
    void windowResized(int w, int h) override;

    Emitter emitter;
    Attractor attractor;
    
    // Where the orbital center is (click to move)
    ofVec2f attractorCenter;
    
    // GUI
    ofxPanel gui;
    ofxFloatSlider bgAlpha;
    ofxFloatSlider particleMass;
    ofxFloatSlider attractorMass;
    ofxIntSlider numParticles;
    ofxFloatSlider pullStrength;
    ofxFloatSlider pushStrength;
    
    int previousNumParticles;
    bool showGui;
};
