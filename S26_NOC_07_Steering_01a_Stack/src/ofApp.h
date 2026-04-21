//
//  ofApp.h
//  S26_NOC_07_Steering_01a_Stack
//
//  Created by Luisa Pinzon
//
// ============================================================
//  EXAMPLE 1A — ONE VEHICLE ON THE STACK
// ============================================================
//
//  Vehicle vehicle;  ← the object lives directly here in memory
//
//  Stack variables:
//  • born when ofApp starts, die when ofApp closes
//  • use  .  to call methods  (vehicle.update())
//  • zero cleanup needed — automatic
//  • BUT: fixed at compile time, can't grow dynamically
//
//  This works perfectly for ONE vehicle.
//  The question we'll ask at the end of class:
//  "What if we want to spawn a new one on every click?"
//

#pragma once
#include "ofMain.h"
#include "vehicle.hpp"

class ofApp : public ofBaseApp {
public:
	void setup()    override;
	void update()   override;
	void draw()     override;
	void exit()     override;
	void keyPressed(int key)                    override;
	void windowResized(int w, int h)            override;
	void mousePressed(int x, int y, int button) override;

private:

	// --------------------------------------------------------
	// STACK — Vehicle lives right here, IS the object itself
	// Use  .  to access:  vehicle.update()
	// --------------------------------------------------------
	Vehicle vehicle;
};
