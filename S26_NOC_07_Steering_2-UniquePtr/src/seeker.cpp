//
//  seeker.cpp
//  S26_NOC_07_Steering_2-UniquePtr
//

#include "seeker.hpp"

Seeker::Seeker(float x, float y) : Vehicle(x, y) {
	maxSpeed = 5.0f;
	maxForce = 0.2f;
	r        = 10.0f;
}

//--------------------------------------------------------------
// Seeker uses the mouse — steers toward it

void Seeker::update(ofVec2f mouse) {
	seek(mouse);              // use mouse position

	velocity     += acceleration;
	velocity.limit(maxSpeed);
	position     += velocity;
	acceleration *= 0;
}

//--------------------------------------------------------------
void Seeker::draw() {
	ofPushMatrix();
	ofTranslate(position.x, position.y);
	ofRotateRad(atan2(velocity.y, velocity.x));

	// ORANGE triangle
	ofSetColor(ofColor::fromHex(0xFF6600));
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
