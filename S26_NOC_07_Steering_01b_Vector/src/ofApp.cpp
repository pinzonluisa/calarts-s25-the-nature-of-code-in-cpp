//
//  ofApp.cpp
//  S26_NOC_07_Steering_01b_Vector
//
//  Created by Luisa Pinzon
//

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);
	swarm.push_back(Vehicle(ofGetWidth() / 2, ofGetHeight() / 2));
}

//--------------------------------------------------------------
void ofApp::update() {
	ofVec2f mouse(ofGetMouseX(), ofGetMouseY());
	for (int i = 0; i < swarm.size(); i++) {
		swarm[i].seek(mouse);
		swarm[i].update();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(0, 25);
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	// draw target
	ofSetColor(255, 80);
	ofNoFill();
	ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 20);
	ofSetColor(255);
	ofFill();
	ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 4);

	for (int i = 0; i < swarm.size(); i++) {
		swarm[i].draw();
	}

	ofSetColor(150);
	ofDrawBitmapString("EXAMPLE 1B — vector<Vehicle>", 10, 20);
	ofDrawBitmapString("Left click = try to spawn Seeker (yellow triangle)", 10, 36);
	ofDrawBitmapString("Right click = try to spawn Wanderer (cyan circle)", 10, 52);
	ofDrawBitmapString("Watch: ALL vehicles draw yellow. Slicing kills polymorphism.", 10, 68);
	ofDrawBitmapString("Vehicles: " + ofToString(swarm.size()), 10, 84);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

	if (button == 0) {
		// --------------------------------------------------------
		// LEFT CLICK — try to add a Seeker
		// --------------------------------------------------------
		// This COMPILES with no errors or warnings.
		// C++ happily accepts a Seeker where a Vehicle is expected.
		// BUT: the vector copies only the Vehicle PART of the Seeker.
		// The Seeker's overridden draw() is lost.
		// Result: draws as a plain yellow base Vehicle, not a Seeker.
		// That's OBJECT SLICING.
		// --------------------------------------------------------
		swarm.push_back(Seeker(x, y));   // ← sliced! Seeker becomes Vehicle
	}

	if (button == 2) {
		// --------------------------------------------------------
		// RIGHT CLICK — try to add a Wanderer
		// --------------------------------------------------------
		// Same problem. Wanderer has 'wanderAngle' as extra data.
		// The vector can't store that — it only has room for Vehicle.
		// wanderAngle gets chopped off. Wanderer update() never runs.
		// Result: draws as a plain yellow base Vehicle, wanders randomly? No.
		// It seeks the mouse like all base Vehicles. Cyan circle? Gone.
		// --------------------------------------------------------
		swarm.push_back(Wanderer(x, y)); // ← sliced! Wanderer becomes Vehicle
	}

	// --------------------------------------------------------
	// THE LESSON:
	// vector<Vehicle> gives us dynamic spawning (good!)
	// but destroys polymorphism (bad!)
	//
	// We need a container that can hold BOTH types at once
	// without slicing. That means storing ADDRESSES instead
	// of objects. That means pointers. → See Example 1C.
	// --------------------------------------------------------
}

//--------------------------------------------------------------
void ofApp::exit() {
	// nothing — vector<Vehicle> cleans itself up automatically
	// (this is actually the one advantage it has over raw pointers)
}

void ofApp::keyPressed(int key) {
	if (key == ' ') {
		swarm.clear();
		ofBackground(0);
		swarm.push_back(Vehicle(ofGetWidth() / 2, ofGetHeight() / 2));
	}
}
void ofApp::windowResized(int w, int h) { }
