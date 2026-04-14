//  mover.hpp
//  A particle that accelerates toward a target position
//
//  The mover does not know where its target comes from —
//  it could be the mouse, a sensor, a network message, anything.
//  That separation makes it reusable in future projects.

#pragma once
#include "ofMain.h"

class mover {
public:
	mover();

	void setup();

	// Update takes a target x/y position to move toward
	// The caller (ofApp) is responsible for providing the right coordinates
	// This keeps the mover decoupled from any specific input source
	void update(float targetX, float targetY);

	void display();

	ofVec2f position;
	ofVec2f velocity;
	ofVec2f acceleration;
	float   topSpeed;
};
