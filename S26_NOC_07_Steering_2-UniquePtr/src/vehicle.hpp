//
//  vehicle.hpp
//  S26_NOC_07_Steering_2-UniquePtr
//
//  Created by Luisa Pinzon
//
// ============================================================
//  VEHICLE — base class
// ============================================================
//
//  Same as before, with one important change:
//
//  update() now takes a mouse position as a parameter.
//  Each derived class decides what to do with it:
//  • Seeker  → uses it to steer toward mouse
//  • Wanderer → ignores it completely
//
//  This means ofApp no longer calls seek() directly.
//  Each vehicle is responsible for its own behavior.
//  ofApp just says "update" — vehicles decide what that means.
//
//  That's the architecture Jake uses:
//  the object knows what it wants to do,
//  the manager (ofApp) just drives the loop.
//

#pragma once
#include "ofMain.h"

class Vehicle {

public:
	Vehicle();
	Vehicle(float x, float y);

	// update now takes mouse — each class uses it differently
	virtual void update(ofVec2f mouse);
	virtual void draw();

	void applyForce(ofVec2f force);
	void seek(ofVec2f target);

protected:
	ofVec2f position;
	ofVec2f velocity;
	ofVec2f acceleration;

	float maxSpeed;
	float maxForce;
	float r;
};
