//
//  mover.hpp
//  S26_NOC_04_PolarCoordinates
//  Created by Luisa Pinzon
//
//  A simple mover that is positioned using POLAR COORDINATES.
//  Instead of setting position with (x, y), we use (r, θ):
//
//  POLAR TO CARTESIAN CONVERSION:
//      x = r × cos(θ)
//      y = r × sin(θ)
//
//  Where:
//      r = radius (distance from center)
//      θ = angle (in radians)
//

#ifndef mover_hpp
#define mover_hpp

#include "ofMain.h"

class Mover {
public:
	Mover();
	
	void setup();
	void update(float radius, float angle);
	void display();
	
	// ----- CARTESIAN POSITION -----
	ofVec2f position;
	
	// ----- POLAR COORDINATES -----
	float r;      // radius (distance from center)
	float theta;  // angle (in radians)
};

#endif /* mover_hpp */
