//  ofApp.h
//  S26_NOC_06_ParticleSystems_P2
//
//  Created by Luisa Pinzon
//
//  SPACE = reset particles
//  F = fullscreen
//  H = hide GUI
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "emitter.hpp"
#include "attractor.hpp"

class ofApp : public ofBaseApp {

public:
	void setup() override;
	void update() override;
	void draw() override;
	
	void keyPressed(int key) override;
	void windowResized(int w, int h) override;
	
	int numParticles;

	Emitter emitter;
	Attractor attractor;
	
	// 3D Lighting and Camera
	ofLight light;
	ofEasyCam cam;
	
	// GUI (only the sliders we want to keep)
	ofxPanel gui;
	ofxFloatSlider bgAlpha;
	ofxFloatSlider particleMass;
	ofxFloatSlider xMove;
	ofxFloatSlider yMove;
	
	bool showGui;
};
