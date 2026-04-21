//
//  vehicle.cpp
//  Used by all three examples: 01a, 01b, 01c
//
//  Created by Luisa Pinzon
//

#include "vehicle.hpp"

//--------------------------------------------------------------
Vehicle::Vehicle() {
	position     = ofVec2f(0, 0);
	velocity     = ofVec2f(0, 0);
	acceleration = ofVec2f(0, 0);
	maxSpeed     = 4.0f;
	maxForce     = 0.15f;
	r            = 10.0f;
}

Vehicle::Vehicle(float x, float y) {
	position     = ofVec2f(x, y);
	velocity     = ofVec2f(0, 0);
	acceleration = ofVec2f(0, 0);
	maxSpeed     = 4.0f;
	maxForce     = 0.15f;
	r            = 10.0f;
}

//--------------------------------------------------------------
void Vehicle::applyForce(ofVec2f force) {
	acceleration += force;
}

//--------------------------------------------------------------
// SEEK — Reynolds' steering formula
//
//  Step 1: desired = direction to target, scaled to maxSpeed
//  Step 2: steer   = desired - velocity  (the correction needed)
//  Step 3: limit   = clamp to maxForce   (personality)

void Vehicle::seek(ofVec2f target) {
	ofVec2f desired = target - position;
	desired.normalize();
	desired *= maxSpeed;

	ofVec2f steer = desired - velocity;
	steer.limit(maxForce);

	applyForce(steer);
}

//--------------------------------------------------------------
void Vehicle::update() {
	velocity     += acceleration;
	velocity.limit(maxSpeed);
	position     += velocity;
	acceleration *= 0;
}

//--------------------------------------------------------------
// Base draw — yellow triangle pointing in direction of travel

void Vehicle::draw() {
	ofPushMatrix();
	ofTranslate(position.x, position.y);
	ofRotateRad(atan2(velocity.y, velocity.x));

	ofSetColor(ofColor::fromHex(0xFFF808));
	ofFill();
	ofBeginShape();
		ofVertex( r * 2,  0);
		ofVertex(-r * 2, -r);
		ofVertex(-r * 2,  r);
	ofEndShape(true);

	ofNoFill();
	ofSetColor(255, 80);
	ofSetLineWidth(1);
	ofBeginShape();
		ofVertex( r * 2,  0);
		ofVertex(-r * 2, -r);
		ofVertex(-r * 2,  r);
	ofEndShape(true);

	ofPopMatrix();
}
