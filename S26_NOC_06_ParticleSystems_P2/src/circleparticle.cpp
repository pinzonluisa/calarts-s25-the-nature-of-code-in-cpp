//
//  circleparticle.cpp
//  S26_NOC_06_ParticleSystems_P2
//
//  Created by Luisa Pinzon on 3/14/26.
//

#include "circleparticle.hpp"

// ============================================================
// CONSTRUCTOR
// ============================================================

CircleParticle::CircleParticle() {
	sides = 32;
	

	particleColor = ofColor::fromHex(0xFFF808).getLerped(
				  ofColor::fromHex(0x80F984), ofRandom(1));
	
//	particleColor = ofColor(255,0,0);
	
}

// ============================================================
// SETUP - Uses parent setup, just ensures correct shape
// ============================================================

void CircleParticle::setup(float orbitRadius, float startAngle) {
	// Call parent's setup first - does all the standard initialization
	Particle::setup(orbitRadius, startAngle);
	// Make sure we're a circle
	sides = 32;
}

// ============================================================
// UPDATE - Standard physics (no modifications from base class)
// ============================================================

void CircleParticle::update(float pullStrength, float pushStrength) {
	// CircleParticle uses exactly the same physics as base Particle
	Particle::update(pullStrength, pushStrength);
}

// ============================================================
// DISPLAY - Standard display (no modifications from base class)
// ============================================================

void CircleParticle::display() {
	Particle::display();
}

// ============================================================
// RESPAWN - Standard respawn anywhere on sphere
// ============================================================

void CircleParticle::respawn() {
	Particle::respawn();
	sides = 32;
}
