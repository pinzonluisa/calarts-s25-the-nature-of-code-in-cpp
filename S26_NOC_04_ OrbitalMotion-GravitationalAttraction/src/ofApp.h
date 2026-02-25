//
//  ofApp.h
//  S25_NOC_05_OrbitalMotion
//
//  Created by Luisa Pinzon
//
//  ============================================
//  ORBITAL MOTION WITH GRAVITATIONAL ATTRACTION
//  ============================================
//
//  This combines:
//  - Polar coordinates (r, θ) for orbital placement
//  - Angular velocity for circular motion
//  - Gravitational attraction affecting orbital radius
//  - Centrifugal push for realistic orbits
//
//  GUI Controls:
//  - Background Alpha: Trail effect
//  - Mover Mass: Mass of orbiting objects
//  - Attractor Mass: Mass of central object (only matters when pull enabled)
//  - Num Movers: How many orbiters
//  - Enable Pull: Toggle chaotic gravity effects
//  - Pull Strength: How strong gravity pulls inward
//  - Push Strength: How strong centrifugal force pushes outward
//
//  Keyboard:
//  - SPACEBAR: Reset movers
//  - F: Toggle fullscreen
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "mover.hpp"
#include "attractor.hpp"

class ofApp : public ofBaseApp {

public:
    void setup() override;
    void update() override;
    void draw() override;
    
    void keyPressed(int key) override;
    void windowResized(int w, int h) override;
   
	//calculate new movers added
    void resetMovers(int count);
	int previousNumMovers;

    // ----- MOVERS -----
    vector<Mover> movers;
    
    // ----- ATTRACTOR -----
    Attractor attractor;
    
    // ----- GUI -----
    ofxPanel gui;
    ofxFloatSlider bgAlpha;
    ofxFloatSlider moverMass;
    ofxFloatSlider attractorMass;
    ofxIntSlider numMovers;
    
    // Orbital chaos controls
    ofxToggle enablePull;
    ofxFloatSlider pullStrength;
    ofxFloatSlider pushStrength;
};
