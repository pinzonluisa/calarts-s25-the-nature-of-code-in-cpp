//
//  ofApp.cpp
//S26_NOC_06_ParticleSystems_P2
//
//  Created by Luisa Pinzon
//

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetBackgroundAuto(false);
	ofBackground(0);
	
	numParticles = 100;
	
	// Enable 3D depth testing - objects in front hide objects behind
	ofEnableDepthTest();
	
	// Setup lighting
	light.setup();
	light.setPosition(200, 300, 500);
	
	// Setup camera - pull back so we can see everything
	cam.setDistance(1000);  // How far back the camera starts
	cam.setNearClip(0.1);
	cam.setFarClip(3000);
	
	// Hardcoded attractor mass
	attractor.setup(800);
	
	// GUI
	gui.setup();
	gui.add(bgAlpha.setup("Background Alpha", 7.6, 0, 255));
	gui.add(particleMass.setup("Particle Mass", 0.2, 0.1, 2.0));
	gui.add(xMove.setup("move X", 0, -ofGetWidth()/2, ofGetWidth()/2));
	gui.add(yMove.setup("move Y", 0, -ofGetHeight()/2, ofGetHeight()/2));
	
	showGui = true;
	
	// Hardcoded 2000 particles
	emitter.setup(numParticles);
}

//--------------------------------------------------------------
void ofApp::update() {
	// Update particle mass from GUI - need to update all 4 vectors
	for (int i = 0; i < emitter.circles.size(); i++) {
		emitter.circles[i].mass = particleMass;
	}
	for (int i = 0; i < emitter.octagons.size(); i++) {
		emitter.octagons[i].mass = particleMass;
	}
	// System position from sliders (already in centered coordinates)
	ofVec2f systemPos(xMove, yMove);
	
	// Attractor smoothly follows slider position
	attractor.updatePosition(systemPos, 0.001);
	
	// Apply attractor force to particles
	emitter.applyAttractor(attractor);
}

//--------------------------------------------------------------
void ofApp::draw() {
	// Disable depth test for 2D drawing (trail effect, GUI)
	ofDisableDepthTest();
	
	// Trail effect
	ofSetColor(0, bgAlpha);
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	glClear(GL_DEPTH_BUFFER_BIT);
	
	// Re-enable depth test for 3D particles
	ofEnableDepthTest();
	ofEnableLighting();
	light.enable();
	
	// Start camera - everything inside cam.begin/end is in 3D
	cam.begin();
	light.setPosition(cam.getPosition());
	ofPushMatrix();
	// Move particle system based on attractor position
	ofTranslate(attractor.position.x, attractor.position.y, 0);
	
	// Hardcoded pull/push strengths
	emitter.run(0.53, 0.26);
	
	ofPopMatrix();
	
	cam.end();
	
	// Disable lighting for 2D elements
	light.disable();
	ofDisableLighting();
	ofDisableDepthTest();
	
	// GUI on top of everything
	if (showGui) {
		gui.draw();
	}
	
	// Info
	ofSetColor(255);
	ofDrawBitmapString("SPACE=reset |  R=reset cam | F=fullscreen | H=GUI | Mouse=rotate camera", 10, ofGetHeight() - 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		ofBackground(0);
		emitter.setup(numParticles);
		
	}
	if (key == 'f' || key == 'F') {
		ofToggleFullscreen();
	}
	if (key == 'h' || key == 'H') {
		showGui = !showGui;
	}
	if (key == 'r' || key == 'R') {
		cam.reset();
		cam.setDistance(1000);
	}
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	ofBackground(0);
}
