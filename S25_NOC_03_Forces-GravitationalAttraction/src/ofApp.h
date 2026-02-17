//
//  ofApp.h
//  S25_NOC_03_Forces-GravitationalAttraction
//
//  Created by Luisa Pinzon
//
//  WHAT THIS EXAMPLE DOES:
//  - Creates multiple Mover objects with random positions and masses
//  - Creates one Attractor in the center
//  - Each mover is pulled toward the attractor via gravitational force
//  - GUI controls: background alpha (for trails), mover mass, and number of movers
//
//  KEY CONCEPTS:
//  - Gravitational attraction: F = G * m1 * m2 / d²
//  - Force accumulation
//  - Newton's second law: A = F / M
//  - std::vector for dynamic arrays
//
//  NEW C++ CONCEPT: std::vector
//  ============================
//  A regular C++ array has a fixed size that can't change:
//      Mover movers[10];  // Always 10, can't add or remove
//
//  std::vector is a dynamic array that can grow or shrink:
//      vector<Mover> movers;  // Starts empty
//      movers.push_back(m);   // Add one
//      movers.size();         // How many are in there?
//      movers.clear();        // Remove all
//
//  Think of it like an ArrayList in Java or a regular array in JavaScript.
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "mover.hpp"
#include "attractor.hpp"

class ofApp : public ofBaseApp {

public:
	void setup() override;
	void update() override;
	void draw() override;
	void exit() override;

	void keyPressed(int key) override;
	void keyReleased(int key) override;
	void mouseMoved(int x, int y) override;
	void mouseDragged(int x, int y, int button) override;
	void mousePressed(int x, int y, int button) override;
	void mouseReleased(int x, int y, int button) override;
	void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
	void mouseEntered(int x, int y) override;
	void mouseExited(int x, int y) override;
	void windowResized(int w, int h) override;
	void dragEvent(ofDragInfo dragInfo) override;
	void gotMessage(ofMessage msg) override;
	
	// Helper function to create/recreate movers
	void resetMovers(int count);

	// ----- MOVERS -----
	// std::vector is a dynamic array - it can grow and shrink!
	// Unlike a regular array, we can add/remove elements at runtime
	
	vector<Mover> movers;
	
	// ----- ATTRACTOR -----
	Attractor attractor;
	
	// ----- GUI -----
	ofxPanel gui;
	ofxFloatSlider bgAlpha;       // Background alpha for trails
	ofxFloatSlider moverMass;     // Mass of all movers
	ofxFloatSlider attractorMass; // Mass of attractor
	ofxIntSlider numMovers;       // Number of movers (can change!)
	
	// Track previous number of movers to detect changes
	int previousNumMovers;
};
