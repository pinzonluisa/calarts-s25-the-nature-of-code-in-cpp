//
//  triangleparticle.cpp
//  S26_NOC_06_ParticleSystems_P2
//
//  Created by Luisa Pinzon on 3/14/26.
//

#include "triangleparticle.hpp"

// ============================================================
// CONSTRUCTOR
// ============================================================

TriangleParticle::TriangleParticle() {
	sides = 3;
	
	// Lime to Green range
	ofColor color1 = ofColor::fromHex(0xBFFC06);
	ofColor color2 = ofColor::fromHex(0x60F904);
	particleColor = color1.getLerped(color2, ofNoise(noiseOffset + 100));
	
//	particleColor = ofColor(0,255,0);
}

// ============================================================
// SETUP - Bigger mass = more centrifugal force
// ============================================================

void TriangleParticle::setup(float orbitRadius, float startAngle) {
	// Call parent setup - does all the standard initialization
	Particle::setup(orbitRadius, startAngle);
	
	// Triangle shape
	sides = 3;

	mass;
}

// ============================================================
// DISPLAY
// ============================================================

void TriangleParticle::display() {
	Particle::display();
}

// ============================================================
// RESPAWN - Outer/front region of sphere
// ============================================================

void TriangleParticle::respawn() {
	Particle::respawn();
	sides = 3;
}
