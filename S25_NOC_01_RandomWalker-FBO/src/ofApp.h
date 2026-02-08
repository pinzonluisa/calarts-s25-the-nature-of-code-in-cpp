//
//  ofApp.h
//  S25_NOC_01_RandomWalker
//
//  Created by Luisa Pinzon on 2/3/25
//

#pragma once

#include "ofMain.h"
#include "walker.hpp"

class ofApp : public ofBaseApp{

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

	// Walker object
	walker randomwalker;
	
	// Frame buffer object - stores the drawing so trails persist
	ofFbo fbo;
};
