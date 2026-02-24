//
//  attractor.cpp
//  S25_NOC_03_Forces-GravitationalAttraction
//
//  Created by Luisa Pinzon
//

#include "attractor.hpp"

Attractor::Attractor() {
	
}

//--------------------------------------------------------------
void Attractor::setup(float x, float y, float m) {
	position = ofVec2f(x, y);
	mass = m;
	G = 0.2;  // Gravitational constant - adjust for stronger/weaker gravity
}

//--------------------------------------------------------------
ofVec2f Attractor::attract(const Mover& mover) {
	// STEP 1: Calculate direction of force
	// Vector pointing FROM mover TO attractor
	ofVec2f direction = position - mover.position;
	
	// STEP 2: Calculate distance (magnitude of that vector)
	// We need this BEFORE normalizing, because normalize makes length = 1
	float distance = direction.length();
	
	// STEP 3: Constrain distance to avoid extreme forces
	// Too close = force explodes to infinity (dividing by tiny number)
	// Too far = force becomes negligible
	distance = ofClamp(distance, 10, 50);
	
	// STEP 4: Calculate magnitude of gravitational force
	// F = G * (m1 * m2) / d²
	float strength = (G * mass * mover.mass) / (distance * distance);
	
	// STEP 5: Build the force vector
	// Start with direction, normalize it (length = 1), then scale to strength
	direction.normalize();
	ofVec2f force = direction * strength;
	
	return force;
}

//--------------------------------------------------------------
void Attractor::display() {
	ofSetColor(100);
	ofFill();
	
	
	// Size based on mass
	float radius = sqrt(mass) * 2;
	ofDrawCircle(position.x, position.y, radius);
}
