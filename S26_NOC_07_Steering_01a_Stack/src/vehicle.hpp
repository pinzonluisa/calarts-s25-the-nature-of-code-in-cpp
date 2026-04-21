//
//  vehicle.hpp
//  Used by all three examples: 01a, 01b, 01c
//
//  Created by Luisa Pinzon
//
// ============================================================
//  VEHICLE — base class
// ============================================================
//
//  Seeks a target using Reynolds' steering formula:
//      steering = desired velocity − current velocity
//
//  'virtual' on update/draw means derived classes can override
//  these methods. Without virtual, the base version always runs
//  even if you call it on a Seeker or Wanderer.
//
//  'protected' means derived classes (Seeker, Wanderer) can
//  read and write these variables — but ofApp cannot directly.
//

#pragma once
#include "ofMain.h"

class Vehicle {

public:
	Vehicle();
	Vehicle(float x, float y);

	virtual void update();
	virtual void draw();           // ← virtual: Seeker and Wanderer draw differently
	void seek(ofVec2f target);
	void applyForce(ofVec2f force);

protected:
	ofVec2f position;
	ofVec2f velocity;
	ofVec2f acceleration;

	float maxSpeed;   // top speed
	float maxForce;   // steering sharpness — defines personality
	float r;          // triangle size
};
