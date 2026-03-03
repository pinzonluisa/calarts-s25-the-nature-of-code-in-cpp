//
//  ofApp.cpp
//  S26_NOC_05-02_ParticleSystems-OpenCV
//  Created by Luisa Pinzon
//

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetBackgroundAuto(false);
	ofBackground(0);
	ofSetCircleResolution(32);
	
	attractor.setup(200);
	
	// Blob tracker
	tracker.setup(640, 480);
	
	// GUI
	gui.setup();
	gui.add(bgAlpha.setup("Background Alpha", 20, 0, 255));
	gui.add(particleMass.setup("Particle Mass", 2, 0.5, 8));
	gui.add(attractorMass.setup("Attractor Mass", 200, 50, 500));
	gui.add(numParticles.setup("Num Particles", 200, 10, 500));
	gui.add(pullStrength.setup("Pull Strength", 0.5, 0.0, 2.0));
	gui.add(pushStrength.setup("Push Strength", 0.1, 0.0, 2.0));
	gui.add(attractorEasing.setup("Attractor Easing", 0.0001, 0.00001, 0.01));
	
	// Blob tracker GUI
	gui.add(threshold.setup("Threshold", 70, 1, 150));
	gui.add(learnBG.setup("Learn Background", false));
	gui.add(showCamera.setup("Show Camera", false));
	
	previousNumParticles = numParticles;
	showGui = true;
	
	emitter.setup(numParticles);
}

//--------------------------------------------------------------
void ofApp::update() {
	// Check if particle count changed
	if (numParticles != previousNumParticles) {
		emitter.setup(numParticles);
		previousNumParticles = numParticles;
	}
	
	// Update masses from GUI
	attractor.mass = attractorMass;
	
	for (int i = 0; i < emitter.particles.size(); i++) {
		emitter.particles[i].mass = particleMass;
	}
	
	// Update blob tracker
	tracker.threshold = threshold;
	tracker.learnBackground = learnBG;
	if (learnBG) learnBG = false;  // Reset toggle
	tracker.update();
	
	// Get blob centroids
	vector<ofVec2f> centroids = tracker.getBlobCentroids(ofGetWidth(), ofGetHeight());
	
	if (centroids.size() > 0) {
		// Use first blob - convert to centered coordinates
		ofVec2f blobPos(centroids[0].x - ofGetWidth()/2,
						centroids[0].y - ofGetHeight()/2);
		attractor.updatePosition(blobPos, attractorEasing);
	}
	
	// Apply attractor force to particles
	emitter.applyAttractor(attractor);
}

//--------------------------------------------------------------
void ofApp::draw() {
	// Trail effect
	ofSetColor(0, bgAlpha);
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	
	// Show camera if enabled
	if (showCamera) {
		tracker.drawContours(0, 0, 320, 240);
	}
	
	if (showGui) {
		gui.draw();
	}
	
	ofPushMatrix();
	ofTranslate(ofGetWidth()/2 + attractor.position.x,
				ofGetHeight()/2 + attractor.position.y);
	
	// Run particle system
	emitter.run(pullStrength, pushStrength);
	
	ofPopMatrix();
	
	// Info
	ofSetColor(255);
	ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate(), 1), 10, ofGetHeight() - 40);
	ofDrawBitmapString("Blobs: " + ofToString(tracker.contourFinder.nBlobs), 10, ofGetHeight() - 25);
	ofDrawBitmapString("SPACE=reset | B=learn BG | F=fullscreen | H=GUI", 10, ofGetHeight() - 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		emitter.setup(numParticles);
		ofBackground(0);
	}
	if (key == 'b' || key == 'B') {
		tracker.learnBackground = true;
	}
	if (key == 'f' || key == 'F') {
		ofToggleFullscreen();
	}
	if (key == 'h' || key == 'H') {
		showGui = !showGui;
	}
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	ofBackground(0);
}
