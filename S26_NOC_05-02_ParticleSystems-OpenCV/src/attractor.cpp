//
//  attractor.cpp
//  S25_NOC_06_ParticleSystem
//
//  Created by Luisa Pinzon
//

#include "attractor.hpp"

Attractor::Attractor() {
    
}

//--------------------------------------------------------------
void Attractor::setup(float m) {
    position = ofVec2f(0, 0);
	velocity = ofVec2f(0,0);
    mass = m;
    G = 1.0;
}

//--------------------------------------------------------------
ofVec2f Attractor::attract(const Particle& particle) {
    ofVec2f direction = position - particle.position;
    float distance = direction.length();
    
    distance = ofClamp(distance, 5, 25);
    
    float strength = (G * mass * particle.mass) / (distance * distance);
    
    direction.normalize();
    ofVec2f force = direction * strength;
    
    return force;
}

void Attractor::updatePosition(ofVec2f target, float easing) {
	// Calculate force toward mouse
	ofVec2f direction = target - position;
	
	// Add to velocity (like acceleration)
	velocity += direction * easing;
	
	// Dampen velocity (friction)
	velocity *= 0.95;
	
	// Update position
	position += velocity;
}

