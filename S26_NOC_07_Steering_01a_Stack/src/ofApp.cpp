//
//  ofApp.cpp
//  S26_NOC_07_Steering_01a_Stack
//
//  Created by Luisa Pinzon
//

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);

	// vehicle already exists on the stack — just initialize it
	// no 'new', no pointer, no cleanup needed
	vehicle = Vehicle(ofGetWidth() / 2, ofGetHeight() / 2);
}

//--------------------------------------------------------------
void ofApp::update() {
	ofVec2f mouse(ofGetMouseX(), ofGetMouseY());

	// vehicle is the object itself → use  .  not  ->
	vehicle.seek(mouse);
	vehicle.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(255, 80);
	ofNoFill();
	ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 20);
	ofSetColor(255);
	ofFill();
	ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 4);

	vehicle.draw();

	ofSetColor(150);
	ofDrawBitmapString("EXAMPLE 1A — STACK", 10, 20);
	ofDrawBitmapString("Vehicle vehicle;  — stack object, use  .  operator", 10, 36);
	ofDrawBitmapString("Vehicles: 1 (always, forever)", 10, 52);
	ofDrawBitmapString("Click = resets vehicle to click position", 10, 68);
	ofDrawBitmapString("Problem: can we spawn MORE on click?", 10, 84);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

	vehicle = Vehicle(x, y);  // for now: just reset to click position
}

//--------------------------------------------------------------
void ofApp::exit() {
	// nothing to clean up — stack handles it automatically
}

void ofApp::keyPressed(int key) { }
void ofApp::windowResized(int w, int h) { }
