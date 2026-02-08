//
//  walker.cpp
//  S25_NOC_01_RandomWalker
//
//  Created by Luisa Pinzon on 2/3/25
//

#include "walker.hpp"

walker::walker(){
	
}

//--------------------------------------------------------------
void walker::setup(){
	x = ofRandom(0, ofGetWidth());
	y = ofRandom(0, ofGetHeight());
}

//--------------------------------------------------------------
void walker::update(){
	// Movement
	float direction = floor(ofRandom(4));
	
	if (direction == 0){
		// Move left
		x = x - 1;   // also: x -= 1; or x--;
	}
	else if (direction == 1){
		// Move right
		x = x + 1;   // also: x += 1; or x++;
	}
	else if (direction == 2){
		// Move down
		y = y + 1;   // also: y += 1; or y++;
	}
	else {
		// Move up
		y = y - 1;   // also: y -= 1; or y--;
	}
	
	// Keep walker on screen
	if (x < 0) x = 0;
	if (x > ofGetWidth()) x = ofGetWidth();
	if (y < 0) y = 0;
	if (y > ofGetHeight()) y = ofGetHeight();
}

//--------------------------------------------------------------
void walker::display(float r, float g, float b, float size){
	ofSetColor(r, g, b);
	ofDrawCircle(x, y, size);
}
