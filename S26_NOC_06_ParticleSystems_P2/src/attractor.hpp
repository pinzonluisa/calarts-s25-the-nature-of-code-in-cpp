//
//  attractor.hpp
//  S26_NOC_06_ParticleSystems_P2
//
//  Created by Luisa Pinzon on 3/14/26.
//

#ifndef attractor_hpp
#define attractor_hpp

#include "ofMain.h"
#include "particle.hpp"

class Attractor {
	
public:
	
	Attractor();
	
	void setup(float m);
	
	// Now returns ofVec3f for 3D particles
	ofVec3f attract(const Particle& particle);
	
	// Smooth following
	ofVec2f velocity;
	void updatePosition(ofVec2f target, float easing);
	
	// Properties
	ofVec2f position;
	float mass;
	
private:
	// Gravitational constant - never changes
	float G;
};

#endif
