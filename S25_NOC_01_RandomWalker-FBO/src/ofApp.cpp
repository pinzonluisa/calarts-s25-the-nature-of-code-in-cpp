//
//  ofApp.cpp
//  S25_NOC_01_RandomWalker
//
//  Created by Luisa Pinzon on 2/3/25
//

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	
	randomwalker.setup();
	
	// Setup the FBO (Frame Buffer Object)
	// This lets us draw into an offscreen image that accumulates over time
	// Without it, the screen clears every frame and we lose the trail
	
	// fbo.allocate(width, height, format)
	// GL_RGBA = Red, Green, Blue, Alpha (transparency)
	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	
	// fbo.begin() / fbo.end()
	// Everything drawn between these goes into the fbo, not the screen
	fbo.begin();
	
	// ofClear(red, green, blue, alpha)
	// Clears the fbo to a color (0-255 for each)
	ofClear(255, 255, 255, 255);  // Clear to white, fully opaque
	
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
	randomwalker.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	// Draw the walker INTO the fbo (this accumulates, creating the trail)
	fbo.begin();
	randomwalker.display(0, 0, 0, 1);
	fbo.end();
	
	// ofSetColor(255) resets the tint to white
	// Without this, the fbo might be tinted by previous ofSetColor calls
	// (like the walker's color), making the image darker or colored
	ofSetColor(255);
	
	// fbo.draw(x, y)
	// Draws the fbo contents to the screen at position x, y
	// This comes AFTER fbo.end() because:
	// 1. First we draw INTO the fbo (begin/end) — like painting on a canvas backstage
	// 2. Then we draw THE fbo to the screen — like showing the canvas to the audience
	fbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
