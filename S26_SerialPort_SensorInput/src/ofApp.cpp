//  ofApp.cpp
//  Connects the sensor and the mover
//  Mapping from sensor space to screen space happens here —
//  not in the sensor (which just reads data) or the mover (which just moves)

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(255);
	ofSetBackgroundAuto(false);

	myMover.setup();

	// Open serial connection to the Circuit Playground Bluefruit
	// To find your port: open Terminal and run "ls /dev/tty.*"
	// Plug the board in, run it again — the new entry is your port
	// Baud rate 9600 confirmed via TouchDesigner settings
	mySensor.setup("/dev/tty.usbmodem2101", 9600);

	// GUI sliders — useful for tweaking without recompiling
	gui.setup();
	gui.add(bgAlpha.setup("Background Alpha", 255, 0, 255));
	gui.add(topSpeed.setup("Top Speed", 5, 1, 20));
}

//--------------------------------------------------------------
void ofApp::update(){
	// Read incoming serial data from the sensor
	mySensor.update();

	// --- Map sensor range to screen coordinates ---
	// The accelerometer outputs values in m/s², ranging roughly -9.8 to 9.8
	// (that's one full gravity in each direction)
	// ofMap translates that range to screen pixel coordinates
	// ofMap(value, inputMin, inputMax, outputMin, outputMax)
	float mappedX = ofMap(mySensor.x, -9.8f, 9.8f, 0, ofGetWidth());
	float mappedY = ofMap(mySensor.y, -9.8f, 9.8f, 0, ofGetHeight());

	// Pass the mapped position to the mover
	// The mover doesn't know or care that this came from a sensor
	myMover.topSpeed = topSpeed;
	myMover.update(mappedX, mappedY);

	// a1 controls the trail effect
	// Touched = alpha 10 (very transparent background = long trail)
	// Not touched = alpha 255 (solid background = no trail)
	if (mySensor.a1 == 1) {
		bgAlpha = 10;
	} else {
		bgAlpha = 255;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	// Draw background with current alpha
	// Lower alpha = more transparent = previous frames show through = trail effect
	ofSetColor(255, bgAlpha);
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	myMover.display();

	// Draw GUI on top of everything
	gui.draw();
}

//--------------------------------------------------------------
// Unused event methods — kept for ofBaseApp compliance
void ofApp::exit(){}
void ofApp::keyPressed(int key){}
void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}
