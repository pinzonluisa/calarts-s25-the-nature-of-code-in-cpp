//
//  ofApp.cpp
//  S26_NOC_07_Steering_2-UniquePtr
//
//  Created by Luisa Pinzon
//

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);

	// --------------------------------------------------------
	// make_unique<Vehicle>(x, y)
	// ← allocates Vehicle on heap, wraps it in unique_ptr
	// ← same as 'new Vehicle(x,y)' but with auto-cleanup
	// --------------------------------------------------------
	swarm.push_back(make_unique<Vehicle>(ofGetWidth() / 2, ofGetHeight() / 2));
}

//--------------------------------------------------------------
void ofApp::update() {
	ofVec2f mouse(ofGetMouseX(), ofGetMouseY());

	for (int i = 0; i < swarm.size(); i++) {
		// --------------------------------------------------------
		// swarm[i] is a unique_ptr<Vehicle>
		// unique_ptr supports -> just like a raw pointer
		// each vehicle decides internally what update() does
		// Seeker seeks mouse, Wanderer ignores it
		// --------------------------------------------------------
		swarm[i]->update(mouse);
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
		swarm[i]->draw();
	}

	ofSetColor(150);
	ofDrawBitmapString("EXAMPLE 2 — unique_ptr  (no manual delete!)", 10, 20);
	ofDrawBitmapString("Left click  = spawn Seeker   (orange triangle — seeks mouse)", 10, 36);
	ofDrawBitmapString("Right click = spawn Wanderer (cyan circle — ignores mouse)", 10, 52);
	ofDrawBitmapString("SPACE = reset", 10, 68);
	ofDrawBitmapString("Vehicles: " + ofToString(swarm.size()), 10, 84);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (button == 0) {
		// make_unique<Seeker> — no raw pointer, no new, no delete
		swarm.push_back(make_unique<Seeker>(x, y));
	}
	if (button == 2) {
		swarm.push_back(make_unique<Wanderer>(x, y));
	}
}

//--------------------------------------------------------------
// EXIT — completely empty!
// --------------------------------------------------------
// Compare to Example 1C exit():
//     for (int i = 0; i < swarm.size(); i++) {
//         delete swarm[i];
//         swarm[i] = nullptr;
//     }
//     swarm.clear();
//
// With unique_ptr: when swarm is destroyed, every unique_ptr
// in it automatically deletes its object. Zero manual cleanup.
// This is the entire point of unique_ptr.
// --------------------------------------------------------

void ofApp::exit() {
	// nothing. unique_ptr handles it.
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		// swarm.clear() destroys all unique_ptrs
		// each unique_ptr automatically deletes its Vehicle
		// no manual delete loop needed
		swarm.clear();
		ofBackground(0);
		swarm.push_back(make_unique<Vehicle>(ofGetWidth() / 2, ofGetHeight() / 2));
	}


}

void ofApp::windowResized(int w, int h) { }
