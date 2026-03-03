//
//  ofApp.h
// S26_NOC_05-02_ParticleSystems-OpenCV
//
//  Created by Luisa Pinzon
//
//  SPACE = reset particles
//  B = learn background
//  F = fullscreen
//  H = hide GUI
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"
#include "emitter.hpp"
#include "attractor.hpp"
#include "blobtracker.hpp"

class ofApp : public ofBaseApp {

public:
	void setup() override;
	void update() override;
	void draw() override;
	
	void keyPressed(int key) override;
	void windowResized(int w, int h) override;

	Emitter emitter;
	Attractor attractor;
	
	// Blob Tracker
	BlobTracker tracker;
	
	// GUI
	ofxPanel gui;
	ofxFloatSlider bgAlpha;
	ofxFloatSlider particleMass;
	ofxFloatSlider attractorMass;
	ofxIntSlider numParticles;
	ofxFloatSlider pullStrength;
	ofxFloatSlider pushStrength;
	ofxFloatSlider attractorEasing;
	
	// Blob tracker GUI
	ofxFloatSlider threshold;
	ofxToggle learnBG;
	ofxToggle showCamera;
	
	int previousNumParticles;
	bool showGui;
};
