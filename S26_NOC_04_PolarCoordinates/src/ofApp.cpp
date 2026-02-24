
//  Created by Luisa Pinzon
//

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(255);
	ofSetCircleResolution(100);
	
	mover.setup();
	
	gui.setup();
	gui.add(r.setup("r", 150, 50, 300));
	gui.add(angleDegrees.setup("angle (degrees)", 45, 0, 360));
}

//--------------------------------------------------------------
void ofApp::update() {
	float angleRadians = ofDegToRad(angleDegrees);
	mover.update(r, angleRadians);
}

//--------------------------------------------------------------
void ofApp::draw() {
	//ofDrawRectangle(0,0,200,400); Before Push, we keep the original origin position (0,0) in the top left corner.
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	
	// ----- ORBIT PATH -----
	ofSetColor(230);
	ofNoFill();
	ofSetLineWidth(2);
	ofDrawCircle(0, 0, r);
	
	// ----- X AND Y AXES -----
	ofSetColor(150);
	ofSetLineWidth(1);
	ofDrawLine(-320, 0, 320, 0);
	ofDrawLine(0, -320, 0, 320);
	
	// ----- RADIUS LINE -----
	ofSetColor(100, 100, 255);
	ofSetLineWidth(3);
	ofDrawLine(0, 0, mover.position.x, mover.position.y);
	
	// ----- MOVER -----
	mover.display();
	
	ofPopMatrix();
	//After Pop the original origin position (0,0), goes back to the top left corner
	
	// ----- GUI (outside the transform) -----
	gui.draw();
}
