//
//  mover.cpp
//  S26_NOC_04_PolarCoordinates
//  Created by Luisa Pinzon
//

#include "mover.hpp"

Mover::Mover() {
	
}

//--------------------------------------------------------------
void Mover::setup() {
	r = 100;
	theta = 0;
	position = ofVec2f(0, 0);
}

//--------------------------------------------------------------
void Mover::update(float radius, float angle) {
	r = radius;
	theta = angle;
	
	// ============================================
	// POLAR TO CARTESIAN CONVERSION
	// x = r × cos(θ)
	// y = r × sin(θ)
	// ============================================
	
	position.x = r * cos(theta);
	position.y = r * sin(theta);
}

//--------------------------------------------------------------
void Mover::display() {
	ofSetColor(255, 100, 100);
	ofFill();
	ofDrawCircle(position.x, position.y, 20);
}
