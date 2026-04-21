//
//  ofApp.cpp
//  S26_NOC_07_Steering_01c_RawPointer
//
//  Created by Luisa Pinzon
//

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);

	// spawn one Seeker to start
	// new Seeker(x,y) → allocates on heap, returns address
	// push_back stores that address in the vector
	swarm.push_back(new Vehicle(ofGetWidth() / 2, ofGetHeight() / 2));
}

//--------------------------------------------------------------
void ofApp::update() {
	ofVec2f mouse(ofGetMouseX(), ofGetMouseY());

	for (int i = 0; i < swarm.size(); i++) {
		// swarm[i] is a Vehicle* (pointer) → use  ->  not  .
		// C++ looks at the actual object at that address
		// and calls the right update() for its type
		swarm[i]->seek(mouse);
		swarm[i]->update();
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
		// polymorphism in action:
		// if swarm[i] points to a Seeker  → Seeker::draw()   runs (yellow triangle)
		// if swarm[i] points to a Wanderer → Wanderer::draw() runs (cyan circle)
		// same line of code, different result — that's polymorphism
		swarm[i]->draw();
	}

	ofSetColor(150);
	ofDrawBitmapString("EXAMPLE 1C — vector<Vehicle*>  RAW POINTERS", 10, 20);
	ofDrawBitmapString("Left click  = spawn Seeker   (ORANGE triangle)", 10, 36);
	ofDrawBitmapString("Right click = spawn Wanderer (cyan circle)", 10, 52);
	ofDrawBitmapString("One loop. Two types. Polymorphism works!", 10, 68);
	ofDrawBitmapString("SPACE = reset  |  WARNING: see exit() for memory cleanup", 10, 100);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

	if (button == 0) {
		// --------------------------------------------------------
		// LEFT CLICK — spawn a Seeker on the heap
		// new Seeker(x,y) returns a Seeker* (pointer to Seeker)
		// vector<Vehicle*> accepts it because Seeker IS a Vehicle
		// No slicing — the full Seeker object lives on the heap
		// --------------------------------------------------------
		swarm.push_back(new Seeker(x, y));
	}

	if (button == 2) {
		// --------------------------------------------------------
		// RIGHT CLICK — spawn a Wanderer on the heap
		// wanderAngle and all Wanderer data is preserved
		// because the full object lives on the heap untouched
		// the vector just stores the address
		// --------------------------------------------------------
		swarm.push_back(new Wanderer(x, y));
	}
}

//--------------------------------------------------------------
// EXIT — manual cleanup required with raw pointers
//
// The vector stores addresses. When vector is cleared,
// the addresses are deleted — but the OBJECTS they pointed
// to are still sitting on the heap, unclaimed, forever.
// We must manually delete each object first.
//
// ← THIS is the cost of raw pointers.
// ← Example 2 (unique_ptr) makes this entire function unnecessary.

void ofApp::exit() {
	for (int i = 0; i < swarm.size(); i++) {
		delete swarm[i];    // free the heap object
		swarm[i] = nullptr; // safety: prevent dangling pointer
	}
	swarm.clear();


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		for (int i = 0; i < swarm.size(); i++)
		delete swarm[i];
		swarm.clear();
		ofBackground(0);
		swarm.push_back(new Seeker(ofGetWidth() / 2, ofGetHeight() / 2));
	}
}

void ofApp::windowResized(int w, int h) { }
