//  mover.cpp
//  A particle that accelerates toward a target position

#include "mover.hpp"

//--------------------------------------------------------------
mover::mover(){}

//--------------------------------------------------------------
void mover::setup(){
	// Start at the center of the screen
	position     = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
	velocity     = ofVec2f(0, 0);
	acceleration = ofVec2f(0, 0);
	topSpeed     = 5;
}

//--------------------------------------------------------------
void mover::update(float targetX, float targetY){
	// Build a direction vector pointing from current position toward the target
	ofVec2f target = ofVec2f(targetX, targetY);
	ofVec2f dir    = target - position;

	// normalize() makes the vector length exactly 1
	// This gives us direction only — magnitude comes from the scale below
	dir.normalize();

	// Scale sets the strength of the pull toward the target
	// Higher = snappier, lower = more floaty
	dir *= 0.5f;

	// Apply direction as acceleration
	acceleration = dir;

	// Accumulate acceleration into velocity
	velocity += acceleration;

	// limit() caps the velocity so it never exceeds topSpeed
	// Without this the mover would accelerate forever
	velocity.limit(topSpeed);

	// Move the position by the current velocity
	position += velocity;
}

//--------------------------------------------------------------
void mover::display(){
	ofSetColor(0);
	ofDrawCircle(position.x, position.y, 24);
}
