//
//  ofApp.cpp
//  S25_NOC_06_ParticleSystem
//
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
    
    // GUI
    gui.setup();
    gui.add(bgAlpha.setup("Background Alpha", 20, 0, 255));
    gui.add(particleMass.setup("Particle Mass", 0.5, 0.2, 4));
    gui.add(attractorMass.setup("Attractor Mass", 200, 50, 500));
    gui.add(numParticles.setup("Num Particles", 200, 10, 500));
    gui.add(pullStrength.setup("Pull Strength", 0.5, 0.0, 2.0));
    gui.add(pushStrength.setup("Push Strength", 0.1, 0.0, 2.0));
    
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
	
	// Mouse position in centered coordinates
	ofVec2f mousePos(ofGetMouseX() - ofGetWidth()/2,
					 ofGetMouseY() - ofGetHeight()/2);
	
	// Attractor smoothly follows mouse
	attractor.updatePosition(mousePos, 0.0001);
	
	// Apply attractor force to particles
	emitter.applyAttractor(attractor);
}
//--------------------------------------------------------------
void ofApp::draw() {
    // Trail effect
    ofSetColor(0, bgAlpha);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	if (showGui) {
		gui.draw();
	}
	
	ofPushMatrix();
    
	// Attractor position is already in centered coordinates
	// So: screen center + attractor offset
	ofTranslate(ofGetWidth()/2 + attractor.position.x,
			    ofGetHeight()/2 + attractor.position.y);
    
    // Run particle system
    emitter.run(pullStrength, pushStrength);
	
	ofPopMatrix();
    
    
    
    // Info 
    ofSetColor(255);
    ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate(), 1), 10, ofGetHeight() - 40);
    ofDrawBitmapString("Particles: " + ofToString(emitter.particles.size()), 10, ofGetHeight() - 25);
    ofDrawBitmapString("CLICK=move | SPACE=reset | F=fullscreen | H=GUI", 10, ofGetHeight() - 10);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == ' ') {
        attractorCenter = ofVec2f(0, 0);
        emitter.setup(numParticles);
        ofBackground(0);
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
