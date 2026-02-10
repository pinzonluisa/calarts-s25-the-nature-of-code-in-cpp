#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(255);
	ofSetBackgroundAuto(false);
	
	myMover.setup();
	
	// Setup GUI
	gui.setup();
	
	// bgAlpha slider: min 0, max 255, default 255 (no trail)
	// Lower values = more trail visible
	gui.add(bgAlpha.setup("Background Alpha", 255, 0, 255));
	
	// topSpeed slider: min 1, max 20, default 5
	gui.add(topSpeed.setup("Top Speed", 5, 1, 20));
}

//--------------------------------------------------------------
void ofApp::update(){
	// Pass topSpeed from GUI to mover
	myMover.topSpeed = topSpeed;
	
	myMover.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	// Draw background with alpha to create trail effect
	// Alpha 255 = solid background (no trail)
	// Alpha 10 = very transparent (long trail)
	ofSetColor(255, bgAlpha);
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	
	myMover.display();
	
	// Draw GUI on top
	gui.draw();
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
