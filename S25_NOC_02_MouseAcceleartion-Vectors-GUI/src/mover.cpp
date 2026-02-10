//
//  mover.cpp
//  S25_NOC_02_MouseAcceleartion-Vectors-GUI
//
//  Created by Luisa Pinzon on 2/9/26.
//

#include "mover.hpp"

//Constructor
mover::mover(){
	
}

//--------------------------------------------------------------
void mover::setup(){
	position = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
	velocity = ofVec2f(0, 0);
	acceleration = ofVec2f(0, 0);
	topSpeed = 5;
}

//--------------------------------------------------------------
void mover::update(){
	// Step 1: Compute direction (vector pointing from position to mouse)
	ofVec2f mouse = ofVec2f(ofGetMouseX(), ofGetMouseY());
	ofVec2f dir = mouse - position;
	
	// Step 2: Normalize (make it length 1)
	//normalize()Control acceleration magnitude, ignore distance
	dir.normalize();
	
	// Step 3: Scale (set the magnitude of acceleration)
	dir *= 0.5;
	
	// Step 4: Set acceleration
	acceleration = dir;
	
	// Apply acceleration to velocity
	velocity += acceleration;
	
	// Limit velocity to topSpeed
	//limit(topSpeed)Prevent velocity from growing forever
	velocity.limit(topSpeed);
	
	// Apply velocity to position
	position += velocity;
}

//--------------------------------------------------------------
void mover::display(){
	ofSetColor(0);
	ofDrawCircle(position.x, position.y, 24);
}
