//
//  ofApp.cpp
//  S25_NOC_05_OrbitalMotion
//
//  Created by Luisa Pinzon
//
//  Press SPACEBAR to reset the movers
//  Press F for fullscreen
//

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(60);
    ofSetBackgroundAuto(false);
    ofBackground(0);
    ofSetCircleResolution(100);
    
    // Attractor at center (we translate, so it's at 0,0)
    attractor.setup(0, 0, 200);
    
    // GUI
    gui.setup();
    gui.add(bgAlpha.setup("Background Alpha", 30, 0, 255));
    gui.add(moverMass.setup("Mover Mass", 2, 0.5, 10));
    gui.add(attractorMass.setup("Attractor Mass", 200, 50, 500));
    gui.add(numMovers.setup("Num Movers", 10, 1, 50));
    
    // Orbital chaos controls
    gui.add(enablePull.setup("Enable Pull", true));
    gui.add(pullStrength.setup("Pull Strength", 0.5, 0.0, 2.0));
    gui.add(pushStrength.setup("Push Strength", 0.1, 0.0, 2.0));
    
    previousNumMovers = numMovers;
    
    resetMovers(numMovers);
}

//--------------------------------------------------------------
void ofApp::resetMovers(int count) {
    movers.clear();
    
    for (int i = 0; i < count; i++) {
        Mover m;
        
        // ============================================
        // OLD: Random Cartesian position
        // ============================================
        // float x = ofRandom(ofGetWidth());
        // float y = ofRandom(ofGetHeight());
        // m.setup(x, y, mass);
        // m.velocity = ofVec2f(ofRandom(-2, 2), ofRandom(-2, 2));
        
        // ============================================
        // NEW: Polar coordinates (orbital placement)
        // ============================================
        // Each mover gets:
        // - Random orbital radius (distance from center)
        // - Random starting angle (position around the orbit)
        
        float orbitRadius = ofRandom(80, 300);
        float startAngle = ofRandom(TWO_PI);
        
        m.setup(orbitRadius, startAngle);
        
        movers.push_back(m);
    }
    
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
    
    // Update each mover
    for (int i = 0; i < movers.size(); i++) {
        // Update mass from GUI
        movers[i].mass = moverMass;
        
        // ============================================
        // GRAVITATIONAL ATTRACTION
        // ============================================
        // This is the same as before!
        // But now the force affects orbital radius (r)
        // instead of position directly.
        //
        // When enablePull is OFF:
        //   - This force is calculated but not used
        //   - Movers orbit in perfect circles
        //   - Attractor mass doesn't matter
        //
        // When enablePull is ON:
        //   - Force affects r (pulls mover closer)
        //   - Creates chaotic elliptical orbits
        //   - Higher attractor mass = stronger pull
        // ============================================
        
        ofVec2f gravityForce = attractor.attract(movers[i]);
        movers[i].applyForce(gravityForce);
        
        // Update physics (pass GUI values)
        movers[i].update(enablePull, pullStrength, pushStrength);
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    // Trail effect
    ofSetColor(0, bgAlpha);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    // ============================================
    // TRANSLATE TO CENTER
    // ============================================
    // This makes (0, 0) the center of the screen
    // Much easier for polar coordinates!
    // Without this, we'd have to add ofGetWidth()/2
    // and ofGetHeight()/2 everywhere.
    // ============================================
    
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    // Draw attractor at center (which is now 0, 0)
    //attractor.display();
    
    // Draw all movers
    for (int i = 0; i < movers.size(); i++) {
        movers[i].display();
    }
    
    ofPopMatrix();
    
    // GUI (outside the transform so it stays in corner)
    gui.draw();
    
    // Frame rate display
    ofSetColor(255);
    ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate(), 1), 10, ofGetHeight() - 20);
    ofDrawBitmapString("SPACE = reset | F = fullscreen", 10, ofGetHeight() - 40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == ' ') {
        resetMovers(numMovers);
    }
    if (key == 'f' || key == 'F') {
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    // Clear background when window resizes
    ofBackground(0);
}
