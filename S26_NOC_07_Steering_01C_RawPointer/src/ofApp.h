//
//  ofApp.h
//  S26_NOC_07_Steering_01c_RawPointer
//
//  Created by Luisa Pinzon
//
// ============================================================
//  EXAMPLE 1C — vector<Vehicle*> FIXES EVERYTHING
// ============================================================
//
//  The fix: store POINTERS (addresses) instead of objects.
//
//  A pointer is always the same size (8 bytes on 64-bit).
//  It doesn't matter if it points to a Vehicle, Seeker, or Wanderer.
//  The vector stores addresses — not the objects themselves.
//  No slicing. No data loss. Polymorphism works.
//
//  Left click  = spawn Seeker   → draws ORANGE TRIANGLE ✓
//  Right click = spawn Wanderer → draws CYAN CIRCLE     ✓
//  Both in the same vector. One loop handles everything.
//
//  THE COST:
//  You must delete every pointer manually in exit().
//  Forget one → memory leak.
//  That's what Example 2 (unique_ptr) solves.
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
	// vector<Vehicle*> — stores ADDRESSES, not objects
	// --------------------------------------------------------
	// Each element is a pointer (memory address).
	// The address can point to a Vehicle, Seeker, or Wanderer.
	// The vector doesn't know or care — it just stores the address.
	//
	// When you call swarm[i]->draw(), C++ looks at the actual
	// object at that address and calls ITS draw() method.
	// Seeker gets Seeker::draw(). Wanderer gets Wanderer::draw().
	// That's polymorphism working correctly.
	//
	// Compare to 1B:
	//   vector<Vehicle>   stores objects  → slicing, polymorphism broken
	//   vector<Vehicle*>  stores addresses → no slicing, polymorphism works
	// --------------------------------------------------------
	vector<Vehicle*> swarm;
};
