//
//  wanderer.cpp
//  S26_NOC_07_Steering_2-UniquePtr
//

#include "wanderer.hpp"

Wanderer::Wanderer(float x, float y) : Vehicle(x, y) {
	maxSpeed    = 2.5f;
	maxForce    = 0.08f;
	r           = 10.0f;
	wanderAngle = ofRandom(TWO_PI);
}

//--------------------------------------------------------------
// Wanderer ignores mouse entirely — steers itself
// 'mouse' parameter is received but not used
// (ofApp passes it to everyone — Wanderer just doesn't care)

void Wanderer::update(ofVec2f mouse) {
	// project a circle ahead of the vehicle
	float circleDistance = 60.0f;
	float circleRadius   = 30.0f;

	ofVec2f ahead       = velocity.getNormalized() * circleDistance;
	wanderAngle        += ofRandom(-0.3f, 0.3f);
	ofVec2f circlePoint = ofVec2f(cos(wanderAngle), sin(wanderAngle)) * circleRadius;

	ofVec2f desired = (position + ahead + circlePoint) - position;
	desired.normalize();
	desired *= maxSpeed;

	ofVec2f steer = desired - velocity;
	steer.limit(maxForce);
	applyForce(steer);

	// wrap around edges
	if (position.x > ofGetWidth())  position.x = 0;
	if (position.x < 0)             position.x = ofGetWidth();
	if (position.y > ofGetHeight()) position.y = 0;
	if (position.y < 0)             position.y = ofGetHeight();

	velocity     += acceleration;
	velocity.limit(maxSpeed);
	position     += velocity;
	acceleration *= 0;
}

//--------------------------------------------------------------
void Wanderer::draw() {
	// CYAN circle
	ofSetColor(ofColor::fromHex(0x02F3FF), 180);
	ofFill();
	ofDrawCircle(position.x, position.y, r * 1.5f);

	ofNoFill();
	ofSetColor(ofColor::fromHex(0x02F3FF), 80);
	ofSetLineWidth(1);
	ofDrawCircle(position.x, position.y, r * 2.5f);
}
