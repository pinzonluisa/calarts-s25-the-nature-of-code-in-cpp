//
//  attractor.cpp
//  S26_NOC_06_ParticleSystems_P2
//
//  Created by Luisa Pinzon on 3/14/26.
//

#include "attractor.hpp"

Attractor::Attractor() {
	
}

//--------------------------------------------------------------
void Attractor::setup(float m) {
	position = ofVec2f(0, 0);
	velocity = ofVec2f(0, 0);
	mass = m;
	G = 1.0;
}

//--------------------------------------------------------------
ofVec3f Attractor::attract(const Particle& particle) {
	// Direction from particle to attractor (in 2D, attractor has no z)
	// We only pull in x and y, not z
	ofVec3f attractorPos3D(position.x, position.y, 0);
	ofVec3f direction = attractorPos3D - particle.position;
	
	float distance = direction.length();
	
	// Clamp distance to avoid extreme forces
	distance = ofClamp(distance, 5, 25);
	
	// Gravitational force formula: F = G * m1 * m2 / d^2
	float strength = (G * mass * particle.mass) / (distance * distance);
	
	direction.normalize();
	ofVec3f force = direction * strength;
	
	return force;
}

//--------------------------------------------------------------
void Attractor::updatePosition(ofVec2f target, float easing) {
	// Calculate force toward target
	ofVec2f direction = target - position;
	
	// Add to velocity (like acceleration)
	velocity += direction * easing;
	
	// Dampen velocity (friction)
	velocity *= 0.95;
	
	// Update position
	position += velocity;
}
