//
//  seeker.cpp
//  S26_NOC_07_Steering_01b_Vector
//

#include "seeker.hpp"

Seeker::Seeker(float x, float y) : Vehicle(x, y) {
	// faster and more agile than base vehicle
	maxSpeed = 5.0f;
	maxForce = 0.2f;
	r        = 10.0f;
}

void Seeker::draw() {
	ofPushMatrix();
	ofTranslate(position.x, position.y);
	ofRotateRad(atan2(velocity.y, velocity.x));

	// YELLOW triangle — Seeker color
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
