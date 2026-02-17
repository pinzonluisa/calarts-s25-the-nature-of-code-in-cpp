//
//  mover.hpp
//  S25_NOC_03_Forces-GravitationalAttraction
//
//  Created by Luisa Pinzon
//
//  A simple object that experiences forces.
//  This version uses gravitational attraction toward an attractor.
//

#ifndef mover_hpp
#define mover_hpp

#include "ofMain.h"

class Mover {
public:
	Mover();
	
	// Initialize with position and mass
	void setup(float x, float y, float m);
	
	// Apply a force to this mover (A = F / M)
	void applyForce(ofVec2f force);
	
	// Update position based on velocity and acceleration
	void update();
	
	// Draw the mover
	void display();
	
	// Check edges and bounce
	void checkEdges();
	
	ofVec2f position;
	ofVec2f velocity;
	ofVec2f acceleration;
	float mass;
};

#endif /* mover_hpp */
