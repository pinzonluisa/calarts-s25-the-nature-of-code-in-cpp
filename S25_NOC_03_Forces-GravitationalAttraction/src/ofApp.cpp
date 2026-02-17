//
//  ofApp.cpp
//  S25_NOC_03_Forces-GravitationalAttraction
//
//  Created by Luisa Pinzon
//
//  HOW TO USE:
//  - Watch movers orbit around the central attractor
//  - Adjust "Background Alpha" to see trails (lower = longer trails)
//  - Adjust "Mover Mass" to change how movers respond to gravity
//  - Adjust "Attractor Mass" to change strength of gravitational pull
//  - Adjust "Num Movers" to add or remove movers dynamically!
//  - Press SPACEBAR to reset movers to random positions
//
//  std::vector CHEAT SHEET:
//  ========================
//  vector<Mover> movers;           // Declare empty vector
//  movers.push_back(mover);        // Add element to end
//  movers.size();                  // Get number of elements
//  movers[i];                      // Access element at index i
//  movers.clear();                 // Remove all elements
//  movers.erase(movers.begin()+i); // Remove element at index i
//

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	// Disable automatic background clearing so we can create trails
	ofSetBackgroundAuto(false);
	
	// Clear to black once at start
	ofBackground(0);
	
	// ----- SETUP ATTRACTOR -----
	// Place attractor in center of screen with large mass
	attractor.setup(ofGetWidth() / 2, ofGetHeight() / 2, 200);
	
	// ----- SETUP GUI -----
	gui.setup();
	
	// Background alpha: 255 = no trails, lower = longer trails
	gui.add(bgAlpha.setup("Background Alpha", 30, 0, 255));
	
	// Mover mass: affects how much they accelerate from gravity
	gui.add(moverMass.setup("Mover Mass", 2, 0.5, 10));
	
	// Attractor mass: affects strength of gravitational pull
	gui.add(attractorMass.setup("Attractor Mass", 200, 50, 500));
	
	// Number of movers: can change dynamically!
	gui.add(numMovers.setup("Num Movers", 10, 2, 50));
	
	// Track the initial number
	previousNumMovers = numMovers;
	
	// ----- SETUP MOVERS -----
	// Create initial set of movers
	resetMovers(numMovers);
}

//--------------------------------------------------------------
void ofApp::resetMovers(int count) {
	// Clear any existing movers
	movers.clear();
	
	// Create new movers and add them to the vector
	for (int i = 0; i < count; i++) {
		Mover m;  // Create a new Mover
		
		float x = ofRandom(ofGetWidth());
		float y = ofRandom(ofGetHeight());
		float mass = ofRandom(1, 5);
		m.setup(x, y, mass);
		
		// Give each mover a small random initial velocity
		// This helps create orbital motion instead of falling straight in
		m.velocity = ofVec2f(ofRandom(-2, 2), ofRandom(-2, 2));
		
		// Add this mover to our vector - array
		movers.push_back(m);
	}
	
	// Clear the screen when resetting
	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update() {
	// Check if number of movers changed
	if (numMovers != previousNumMovers) {
		resetMovers(numMovers);
		previousNumMovers = numMovers;
	}
	
	// Update attractor mass from GUI
	attractor.mass = attractorMass;
	
	// For each mover...
	// movers.size() returns how many movers are in the vector
	for (int i = 0; i < movers.size(); i++) {
		// Update mover mass from GUI
		movers[i].mass = moverMass;
		
		// Calculate gravitational force from attractor
		ofVec2f force = attractor.attract(movers[i]);
		
		// Apply the force to the mover
		movers[i].applyForce(force);
		
		// Update mover physics (Euler integration)
		movers[i].update();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	// ----- DRAW SEMI-TRANSPARENT BACKGROUND FOR TRAILS -----
	// Instead of clearing the screen, draw a rectangle with alpha
	// This lets previous frames show through, creating trails
	ofSetColor(0, bgAlpha);
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	
	// ----- DRAW ATTRACTOR -----
	attractor.display();
	
	// ----- DRAW ALL MOVERS -----
	// movers.size() tells us how many movers are currently in the vector
	for (int i = 0; i < movers.size(); i++) {
		movers[i].display();
	}
	
	// ----- DRAW GUI -----
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::exit() {

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	// SPACEBAR resets movers to random positions
	if (key == ' ') {
		resetMovers(numMovers);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	// Update attractor position when window size changes
	attractor.position = ofVec2f(w / 2, h / 2);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
