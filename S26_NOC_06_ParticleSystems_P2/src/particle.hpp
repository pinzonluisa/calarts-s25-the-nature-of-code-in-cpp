//
//  particle.hpp
//  S26_NOC_06_ParticleSystems_P2
//
//  Created by Luisa Pinzon on 3/14/26.

//  BASE PARTICLE CLASS
//  ===================
//  This is the parent class that all particle types inherit from.
//  It defines the common behavior and properties shared by all particles.
//
//  -----------------
//  • virtual methods: Allow derived classes to override behavior
//  • protected members: Accessible by derived classes, but not outside code
//  • private members: Only accessible within this class
//
//  INHERITANCE HIERARCHY:
//  ----------------------
//  Particle (this class)
//      ├── CircleParticle    — stable orbit, baseline behavior
//      ├── TriangleParticle  — bigger, floats outward
//      ├── HexagonParticle   — smaller, sinks inward
//      └── OctagonParticle   — oscillates in and out
//

#ifndef particle_hpp
#define particle_hpp

#include "ofMain.h"

class Particle {
	
// ============================================================
// PUBLIC: Anyone can access these
// ============================================================
public:
	
	// Constructor
	Particle();
	
	// ------------------------------------------------------------
	// VIRTUAL METHODS - Derived classes can override these
	// ------------------------------------------------------------
	// The 'virtual' keyword tells C++: "Look for overrides in derived classes"
	// Without virtual, calling display() on a TriangleParticle would
	// run Particle::display() instead of TriangleParticle::display()
	
	virtual void setup(float orbitRadius, float startAngle);
	virtual void update(float pullStrength, float pushStrength);
	virtual void display();
	virtual void respawn();
	
	// ------------------------------------------------------------
	// NON-VIRTUAL METHODS - Same behavior for all particle types
	// ------------------------------------------------------------
	
	void applyForce(ofVec3f force);
	bool isDead();
	
	// ------------------------------------------------------------
	// PUBLIC PROPERTIES - Other classes need to read/write these
	// ------------------------------------------------------------
	
	// 3D position - now using ofVec3f instead of ofVec2f!
	// z-depth creates the sphere effect when particles respawn
	ofVec3f position;
	
	// Physics properties
	float mass;
	float lifespan;
	
	// Visual properties
	ofColor particleColor;
	int sides;  // Circle resolution: 3=triangle, 6=hexagon, 8=octagon, 32=circle
	
	
// ============================================================
// PROTECTED: Only this class AND derived classes can access
// ============================================================
protected:
	
	// Polar coordinates - used internally for orbital motion
	// Protected because derived classes need to modify 'r' for
	// their unique physics (triangle pushes out, hexagon pulls in)
	float r;              // Distance from center
	float theta;          // Angle around center
	float angularVelocity;
	
	// Acceleration accumulator - reset each frame
	ofVec3f acceleration;
	
	// Perlin noise offset - each particle has a unique seed
	float noiseOffset;
	
	// Track if particle has respawned into 3D sphere yet
	// Particles start in 2D, then transition to 3D positions on first death
	bool hasRespawned;
	
	// Helper method to convert polar (r, theta) to cartesian (x, y)
	// z is handled separately for the 3D sphere effect
	void updatePositionFromPolar();
	
};

#endif
