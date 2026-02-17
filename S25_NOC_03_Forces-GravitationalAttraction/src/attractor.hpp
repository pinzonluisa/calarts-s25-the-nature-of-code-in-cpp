//
//  attractor.hpp
//  S25_NOC_03_Forces-GravitationalAttraction
//
//  Created by Luisa Pinzon
//
//  An object that attracts Mover objects using gravitational force.
//
//  GRAVITATIONAL ATTRACTION FORMULA:
//  F = G * (m1 * m2) / d²
//
//  - G = gravitational constant (we use 1.0 for simplicity)
//  - m1, m2 = masses of the two objects
//  - d = distance between them
//  - Direction: points from mover toward attractor
//

#ifndef attractor_hpp
#define attractor_hpp

#include "ofMain.h"
#include "mover.hpp"

class Attractor {
public:
	Attractor();
	
	void setup(float x, float y, float m);
	
	// Calculate the gravitational force this attractor exerts on a mover
	// Returns a force vector to be applied to the mover
	// This is a METHOD that RETURNS an ofVec2f (a vector).
	// It receives a Mover object to perform its calculation.
	ofVec2f attract(Mover mover);
	
	void display();
	
	// ----- VARIABLES (Properties/Attributes) -----
	// These are not methods — they're variables that store data.
	// Each Attractor object will have its own copy of these.
	
	ofVec2f position;
	float mass;
	float G;  // Gravitational constant
};

#endif /* attractor_hpp */
