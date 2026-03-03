//
//  blobtracker.hpp
//  S26_NOC_05-02_ParticleSystems-OpenCV
//
//  Created by Luisa Pinzon on 3/3/26.
//
//  A reusable OpenCV blob tracking class.
//  Handles camera input, background subtraction, and contour detection.
//  Outputs detected points that can be used by any other system.
//
//  USAGE:
//  ------
//  1. Add to your project (requires ofxOpenCv addon)
//  2. In ofApp.h:
//       #include "BlobTracker.hpp"
//       BlobTracker tracker;
//
//  3. In setup():
//       tracker.setup(640, 480);
//
//  4. In update():
//       tracker.update();
//       vector<ofVec2f> points = tracker.getScaledPoints(ofGetWidth(), ofGetHeight());
//
//  5. In draw() (optional, for debugging):
//       tracker.drawDebug(0, 0, 320, 240);
//
//  6. Add GUI controls:
//       gui.add(tracker.threshold.setup("Threshold", 70, 1, 150));
//       gui.add(tracker.learnBackground.setup("Learn BG", false));
//

#ifndef blobtracker_hpp
#define blobtracker_hpp

#include "ofMain.h"
#include "ofxOpenCv.h"

class BlobTracker {
public:
	BlobTracker();
	
	void setup(int camWidth = 640, int camHeight = 480);
	void update();
	
	// Get detected points scaled to any size
	vector<ofVec2f> getScaledPoints(float targetWidth, float targetHeight);
	
	// Get raw points (camera resolution)
	vector<ofVec2f> getRawPoints();
	
	// Get blob centroids only (one point per blob)
	vector<ofVec2f> getBlobCentroids(float targetWidth, float targetHeight);
	
	// Debug drawing
	void drawDebug(float x, float y, float w, float h);
	void drawCamera(float x, float y, float w, float h);
	void drawContours(float x, float y, float w, float h);
	
	// Camera
	ofVideoGrabber camera;
	float camWidth;
	float camHeight;
	
	// OpenCV images
	ofxCvColorImage colorImg;
	ofxCvGrayscaleImage grayImg;
	ofxCvGrayscaleImage backgroundImg;
	ofxCvGrayscaleImage diffImg;
	
	// Contour finder
	ofxCvContourFinder contourFinder;
	
	// Settings (can be connected to GUI)
	float threshold;
	bool learnBackground;
	
	// Detection settings
	int minBlobArea;
	int maxBlobArea;
	int maxBlobs;
	bool findHoles;
	
private:
	vector<ofVec2f> detectedPoints;
	bool backgroundLearned;
};

#endif
