//
//  particle.cpp
//  S26_NOC_06_ParticleSystems_P2
//
//  Created by Luisa Pinzon on 3/14/26.

#include "particle.hpp"

// ============================================================
// CONSTRUCTOR & DESTRUCTOR
// ============================================================

Particle::Particle() {
	// Each particle gets a unique noise offset
	noiseOffset = ofRandom(5000);
	
	// Default to circle (smooth, 32 sides)
	sides = 32;
	
	// Particle starts in 2D, hasn't respawned into 3D sphere yet
	hasRespawned = false;
}

// ============================================================
// SETUP - Initialize particle with orbital position
// ============================================================

void Particle::setup(float orbitRadius, float startAngle) {
	// Use Perlin noise for mass variation
	// ofNoise returns 0.0 to 1.0, so we map it to our desired range
	// Adding noiseOffset makes each particle different
	mass = ofMap(ofNoise(noiseOffset), 0, 1, 1.0, 5.0);
	
	// Polar coordinates
	r = orbitRadius;
	theta = startAngle;
	
	// Angular velocity - smaller radius = faster orbit (Kepler's law!)
	angularVelocity = 2.0 / r;
	
	// Initialize 3D position (start with z = 0, flat plane)
	position = ofVec3f(0, 0, 0);
	updatePositionFromPolar();
	
	// Reset acceleration
	acceleration = ofVec3f(0, 0, 0);
	
	// Full opacity to start
	lifespan = 255;
}

// ============================================================
// APPLY FORCE - Accumulate forces (called by attractor)
// ============================================================

void Particle::applyForce(ofVec3f force) {
	// F = ma, so a = F/m
	ofVec3f a = force / mass;
	acceleration += a;
}

// ============================================================
// UPDATE - Physics simulation (can be overridden by derived classes)
// ============================================================

void Particle::update(float pullStrength, float pushStrength) {
	// Update angular velocity based on current radius
	angularVelocity = 2.0 / r;

	theta += angularVelocity;
	
	// Gravitational pull - acceleration pulls particle inward
	float gravitationalPull = acceleration.length();
	r -= gravitationalPull * pullStrength;
	
	// Centrifugal push - based on mass and angular velocity
	float centrifugalPush = mass * angularVelocity * angularVelocity * r * 20;
	r += centrifugalPush * pushStrength;
	
	// Clamp radius to valid range
	r = ofClamp(r, 5, 500);
	
	// Lifespan fades as particle approaches center
	lifespan = ofMap(r, 5, 500, 10, 255, true);
	
	// Convert polar to cartesian (updates position.x and position.y)
	updatePositionFromPolar();
	
	// Clear acceleration for next frame
	acceleration *= 0;
}

// ============================================================
// HELPER - Convert polar coordinates to cartesian position
// ============================================================

void Particle::updatePositionFromPolar() {
	position.x = r * cos(theta);
	position.y = r * sin(theta);
	// Note: position.z is set in respawn() for 3D sphere effect
}

// ============================================================
// IS DEAD - Check if particle should respawn
// ============================================================

bool Particle::isDead() {
	return r <= 60;
}

// ============================================================
// RESPAWN - Reset particle to outer edge, now in 3D!
// ============================================================

void Particle::respawn() {
	hasRespawned = true;

	// New orbital radius (2D)
	float radiusNoise = ofNoise(noiseOffset);
	r = ofMap(radiusNoise, 0, 1, 50, 400);

	theta = ofRandom(TWO_PI);
	angularVelocity = 2.0 / r;
	lifespan = 255;

	// Update x, y from polar
	updatePositionFromPolar();


	float zSign = (ofRandom(1) > 0.5) ? 1.0 : -1.0;
	position.z = ofRandom(50, 500) * zSign;
}

// ============================================================
// DISPLAY - Draw the particle as a real 3D sphere
// ============================================================

void Particle::display() {
	// Calculate visual size from mass
	float radius = sqrt(mass) * 8;
	
	// Set material color
	ofSetColor(particleColor, lifespan);
	
	// Draw real 3D sphere at x, y, z position
	ofDrawSphere(position.x, position.y, position.z, radius);
}
