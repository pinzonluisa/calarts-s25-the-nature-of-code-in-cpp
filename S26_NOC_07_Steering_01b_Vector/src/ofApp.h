//
//  ofApp.h
//  S26_NOC_07_Steering_01b_Vector
//
//  Created by Luisa Pinzon
//
// ============================================================
//  EXAMPLE 1B — vector<Vehicle> WORKS FOR SPAWNING
//                BUT BREAKS POLYMORPHISM
// ============================================================
//
//  Good news: vector<Vehicle> lets us spawn on click!
//  Bad news:  it can only hold plain Vehicle objects.
//
//  OBJECT SLICING — the hidden problem:
//  When you push a Seeker or Wanderer into vector<Vehicle>,
//  the vector COPIES only the Vehicle part of the object.
//  All the extra Wanderer data (wanderAngle etc.) is chopped off.
//  The Wanderer becomes a plain Vehicle. It "forgets" how to wander.
//  virtual methods stop working correctly.
//
//  Left click  = spawn Seeker  (tries to draw yellow triangle)
//  Right click = spawn Wanderer (tries to draw cyan circle)
//  Watch what actually happens → both draw as plain Vehicles
//

#pragma once
#include "ofMain.h"
#include "vehicle.hpp"
#include "seeker.hpp"
#include "wanderer.hpp"
#include <vector>

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
	// vector<Vehicle> — stores OBJECTS directly
	// --------------------------------------------------------
	// Good: spawning works, dynamic size, no pointers needed
	// Bad:  can only hold the BASE class type
	//       pushing a Seeker or Wanderer causes OBJECT SLICING
	//
	// Try it: push_back(Seeker(x,y)) — it compiles!
	// But the Seeker draw() never runs. Base draw() runs instead.
	// That's slicing.
	// --------------------------------------------------------
	vector<Vehicle> swarm;
};
