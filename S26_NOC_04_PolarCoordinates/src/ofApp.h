//  Created by Luisa Pinzon
//
//  POLAR COORDINATES DEMONSTRATION
//  ================================
//
//  CARTESIAN: Position is (x, y)
//  POLAR:     Position is (r, θ)
//
//  CONVERSION:
//      x = r × cos(θ)
//      y = r × sin(θ)
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "mover.hpp"

class ofApp : public ofBaseApp {

public:
	void setup() override;
	void update() override;
	void draw() override;

	// ----- MOVER -----
	Mover mover;
	
	// ----- GUI -----
	ofxPanel gui;
	ofxFloatSlider r;
	ofxFloatSlider angleDegrees;
};
