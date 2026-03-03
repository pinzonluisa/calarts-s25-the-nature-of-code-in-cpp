//
//  blobtracker.cpp
//  S26_NOC_05-02_ParticleSystems-OpenCV
//
//  Created by Luisa Pinzon on 3/3/26.
//
#include "blobtracker.hpp"

BlobTracker::BlobTracker() {
	threshold = 70;
	learnBackground = false;
	backgroundLearned = false;
	
	minBlobArea = 100;
	maxBlobs = 10;
	findHoles = false;
}

//--------------------------------------------------------------
void BlobTracker::setup(int w, int h) {
	camWidth = w;
	camHeight = h;
	
	// Setup camera
	camera.setup(camWidth, camHeight);
	
	// Allocate OpenCV images
	colorImg.allocate(camWidth, camHeight);
	grayImg.allocate(camWidth, camHeight);
	backgroundImg.allocate(camWidth, camHeight);
	diffImg.allocate(camWidth, camHeight);
	
	// Max blob area = full camera
	maxBlobArea = camWidth * camHeight;
}

//--------------------------------------------------------------
void BlobTracker::update() {
	camera.update();
	
	if (camera.isFrameNew()) {
		// Get color image from camera
		colorImg.setFromPixels(camera.getPixels());
		
		// Convert to grayscale
		grayImg = colorImg;
		
		// Learn background if requested
		if (learnBackground) {
			backgroundImg = grayImg;
			backgroundLearned = true;
			learnBackground = false;  // Reset flag
		}
		
		// Only do detection if we have a background
		if (backgroundLearned) {
			// Background subtraction
			diffImg.absDiff(backgroundImg, grayImg);
			
			// Threshold
			diffImg.threshold(threshold);
			
			// Find contours
			contourFinder.findContours(diffImg, minBlobArea, maxBlobArea, maxBlobs, findHoles);
			
			// Extract all contour points
			detectedPoints.clear();
			for (int i = 0; i < contourFinder.nBlobs; i++) {
				for (int j = 0; j < contourFinder.blobs[i].pts.size(); j++) {
					detectedPoints.push_back(contourFinder.blobs[i].pts[j]);
				}
			}
		}
	}
}

//--------------------------------------------------------------
vector<ofVec2f> BlobTracker::getScaledPoints(float targetWidth, float targetHeight) {
	vector<ofVec2f> scaledPoints;
	
	float scaleX = targetWidth / camWidth;
	float scaleY = targetHeight / camHeight;
	
	for (int i = 0; i < detectedPoints.size(); i++) {
		ofVec2f scaled;
		scaled.x = detectedPoints[i].x * scaleX;
		scaled.y = detectedPoints[i].y * scaleY;
		scaledPoints.push_back(scaled);
	}
	
	return scaledPoints;
}

//--------------------------------------------------------------
vector<ofVec2f> BlobTracker::getRawPoints() {
	return detectedPoints;
}

//--------------------------------------------------------------
vector<ofVec2f> BlobTracker::getBlobCentroids(float targetWidth, float targetHeight) {
	vector<ofVec2f> centroids;
	
	float scaleX = targetWidth / camWidth;
	float scaleY = targetHeight / camHeight;
	
	for (int i = 0; i < contourFinder.nBlobs; i++) {
		ofVec2f centroid;
		centroid.x = contourFinder.blobs[i].centroid.x * scaleX;
		centroid.y = contourFinder.blobs[i].centroid.y * scaleY;
		centroids.push_back(centroid);
	}
	
	return centroids;
}

//--------------------------------------------------------------
void BlobTracker::drawDebug(float x, float y, float w, float h) {
	// Draw all CV stages side by side
	float imgW = w / 4;
	float imgH = h;
	
	ofSetColor(255);
	
	// Original camera
	colorImg.draw(x, y, imgW, imgH);
	
	// Grayscale
	grayImg.draw(x + imgW, y, imgW, imgH);
	
	// Background
	backgroundImg.draw(x + imgW * 2, y, imgW, imgH);
	
	// Difference (thresholded)
	diffImg.draw(x + imgW * 3, y, imgW, imgH);
	
	// Labels
	ofDrawBitmapString("Camera", x + 5, y + 15);
	ofDrawBitmapString("Gray", x + imgW + 5, y + 15);
	ofDrawBitmapString("Background", x + imgW * 2 + 5, y + 15);
	ofDrawBitmapString("Diff", x + imgW * 3 + 5, y + 15);
}

//--------------------------------------------------------------
void BlobTracker::drawCamera(float x, float y, float w, float h) {
	ofSetColor(255);
	colorImg.draw(x, y, w, h);
}

//--------------------------------------------------------------
void BlobTracker::drawContours(float x, float y, float w, float h) {
	ofSetColor(255);
	diffImg.draw(x, y, w, h);
	
	// Draw contours on top
	float scaleX = w / camWidth;
	float scaleY = h / camHeight;
	
	ofPushMatrix();
	ofTranslate(x, y);
	ofScale(scaleX, scaleY);
	
	ofNoFill();
	ofSetColor(255, 0, 0);
	for (int i = 0; i < contourFinder.nBlobs; i++) {
		contourFinder.blobs[i].draw();
		
		// Draw centroid
		ofFill();
		ofDrawCircle(contourFinder.blobs[i].centroid, 5);
		ofNoFill();
	}
	
	ofPopMatrix();
}
