//
//  wanderer.cpp
//  S26_NOC_07_Steering_01b_Vector
//
//  Created by Luisa Pinzon on 4/20/26.
//


#include "wanderer.hpp"

Wanderer::Wanderer(float x, float y) : Vehicle(x, y) {
	maxSpeed    = 2.5f;
	maxForce    = 0.08f;
	r           = 10.0f;
	wanderAngle = ofRandom(TWO_PI);  // ← EXTRA data, unique to Wanderer
}

//--------------------------------------------------------------
// WANDER — projects a circle ahead, picks random point on it

void Wanderer::update() {
	// project a circle in front of the vehicle
	float circleDistance = 60.0f;  // how far ahead the circle is
	float circleRadius   = 30.0f;  // how big the circle is

	// direction vehicle is currently moving
	ofVec2f ahead = velocity.getNormalized() * circleDistance;

	// pick a point on the circle, shifting angle slightly each frame
	wanderAngle += ofRandom(-0.3f, 0.3f);
	ofVec2f circlePoint = ofVec2f(cos(wanderAngle), sin(wanderAngle)) * circleRadius;

	// desired = ahead + circlePoint → a point just off our path
	ofVec2f desired = (position + ahead + circlePoint) - position;
	desired.normalize();
	desired *= maxSpeed;

	ofVec2f steer = desired - velocity;
	steer.limit(maxForce);
	applyForce(steer);

	// wrap around screen edges
	if (position.x > ofGetWidth())  position.x = 0;
	if (position.x < 0)             position.x = ofGetWidth();
	if (position.y > ofGetHeight()) position.y = 0;
	if (position.y < 0)             position.y = ofGetHeight();

	// call parent update for physics integration
	Vehicle::update();
}

//--------------------------------------------------------------
// Draw as a CYAN circle — visually different from Seeker

void Wanderer::draw() {
	ofSetColor(ofColor::fromHex(0x02F3FF), 180);
	ofFill();
	ofDrawCircle(position.x, position.y, r * 1.5f);

	ofNoFill();
	ofSetColor(ofColor::fromHex(0x02F3FF), 100);
	ofSetLineWidth(1);
	ofDrawCircle(position.x, position.y, r * 2.5f);
}
