//
//  octagonparticle.cpp
//  S26_NOC_06_ParticleSystems_P2
//
//  Created by Luisa Pinzon on 3/14/26.
//

#include "octagonparticle.hpp"

// ============================================================
// CONSTRUCTOR
// ============================================================

OctagonParticle::OctagonParticle() {
	sides = 8;
	oscillationSpeed = ofRandom(0.1, 3.0);
	
	particleColor = ofColor::fromHex(0x02F3FF).getLerped(
				  ofColor::fromHex(0x80F984), ofRandom(1));
	
//	particleColor = ofColor(255,255,0);
}

// ============================================================
// SETUP
// ============================================================

void OctagonParticle::setup(float orbitRadius, float startAngle) {
	// Call parent setup
	Particle::setup(orbitRadius, startAngle);
	
	// Octagon shape
	sides = 8;
	
	// Vary oscillation speed using Perlin noise
	oscillationSpeed = ofMap(ofNoise(noiseOffset + 500), 0, 1, 0.5, 2.0);
}

// ============================================================
// UPDATE - Modified physics: OSCILLATES IN AND OUT
// ============================================================

void OctagonParticle::update(float pullStrength, float pushStrength) {
	// Update angular velocity based on current radius
	angularVelocity = 2.0 / r;
	
	// Rotate around center
	theta += angularVelocity;
	
	// Gravitational pull (standard)
	float gravitationalPull = acceleration.length();
	r -= gravitationalPull * pullStrength;
	
	// Centrifugal push (standard)
	float centrifugalPush = mass * angularVelocity * angularVelocity * r * 20;
	r += centrifugalPush * pushStrength;
	
	// --------------------------------------------------------
	// OSCILLATION - The unique octagon behavior!
	// --------------------------------------------------------
	// sin() returns values from -1 to 1
	// We use elapsed time + noiseOffset so each particle oscillates differently
	// The result: particles "breathe" in and out
	
	float time = ofGetElapsedTimef() * oscillationSpeed;
	float oscillation = sin(time + noiseOffset) * 2.0;
	r += oscillation;
	
	// Clamp radius
	r = ofClamp(r, 5, 500);
	
	// Update lifespan
	lifespan = ofMap(r, 5, 500, 10, 255, true);
	
	// Update position
	updatePositionFromPolar();
	
	// Clear acceleration
	acceleration *= 0;
}

// ============================================================
// DISPLAY
// ============================================================

void OctagonParticle::display() {
	Particle::display();
}

// ============================================================
// RESPAWN - Equator of sphere, evenly distributed
// ============================================================

void OctagonParticle::respawn() {
	Particle::respawn();
	sides = 8;

	// Set new radius and angle
	r = ofRandom(50, 300);
	theta = ofRandom(TWO_PI);
	
	// Randomize oscillation speed
	oscillationSpeed = ofRandom(0.1, 3.0);
	
	// Update x,y from polar
	updatePositionFromPolar();
	
	// Equator - z near zero
	position.z = ofRandom(-200, 200);
}
