//
//  mover.cpp
//  S25_NOC_03_Forces-GravitationalAttraction
//
//  Created by Luisa Pinzon
//

#include "mover.hpp"

Mover::Mover() {
	
}

//--------------------------------------------------------------
void Mover::setup(float x, float y, float m) {
	position = ofVec2f(x, y);
	velocity = ofVec2f(0, 0);
	acceleration = ofVec2f(0, 0);
	mass = m;
}

//--------------------------------------------------------------
void Mover::applyForce(ofVec2f force) {
	// Newton's second law: A = F / M
	// We calculate the acceleration caused by this force
	// and add it to the total acceleration (force accumulation)
	ofVec2f a = force / mass;
	acceleration += a;
}

//--------------------------------------------------------------
void Mover::update() {
	// Euler integration:
	// 1. Acceleration changes velocity
	// 2. Velocity changes position
	velocity += acceleration;
	position += velocity;
	
	// Clear acceleration for next frame
	// Forces must be re-applied each frame!
	acceleration *= 0;
}

//--------------------------------------------------------------
void Mover::display() {
	ofSetColor(255, 200);
	//ofFill();
	
	// Size based on mass using sqrt for accurate area representation
	// Area = πr², so if mass ∝ area, then r = √mass
	float radius = sqrt(mass) * 5;
	ofDrawCircle(position.x, position.y, radius);
}

//--------------------------------------------------------------
void Mover::checkEdges() {
	// Bounce off edges
	if (position.x < 0) {
		position.x = 0;
		velocity.x *= -1;
	} else if (position.x > ofGetWidth()) {
		position.x = ofGetWidth();
		velocity.x *= -1;
	}
	
	if (position.y < 0) {
		position.y = 0;
		velocity.y *= -1;
	} else if (position.y > ofGetHeight()) {
		position.y = ofGetHeight();
		velocity.y *= -1;
	}
}
