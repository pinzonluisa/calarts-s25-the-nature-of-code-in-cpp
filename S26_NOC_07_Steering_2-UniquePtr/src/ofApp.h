//
//  ofApp.h
//  S26_NOC_07_Steering_02_UniquePtr
//
//  Created by Luisa Pinzon
//
// ============================================================
//  EXAMPLE 2 — unique_ptr
// ============================================================
//
//  Same behavior as Example 1C (raw pointers).
//  Same polymorphism. Same mixed types. Same -> operator.
//
//  The only difference: unique_ptr manages memory automatically.
//  You never write 'delete'. exit() is completely empty.
//
//  WHAT CHANGED FROM 1C:
//  -------------------------------------------------------
//  1C:  vector<Vehicle*>              → raw pointer
//  2:   vector<unique_ptr<Vehicle>>   → smart pointer
//
//  1C:  swarm.push_back(new Vehicle(x,y))
//  2:   swarm.push_back(make_unique<Vehicle>(x,y))
//
//  1C:  exit() has a full delete loop
//  2:   exit() is empty — unique_ptr deletes automatically
//  -------------------------------------------------------
//
//  Everything else — the loop, the ->, the polymorphism —
//  is identical. That's the point.
//
//  WHAT IS unique_ptr?
//  A wrapper around a raw pointer that automatically calls
//  delete when the pointer goes out of scope or is removed
//  from the vector. One owner only — hence "unique".
//

#pragma once
#include "ofMain.h"
#include "vehicle.hpp"
#include "seeker.hpp"
#include "wanderer.hpp"
#include <vector>
#include <memory>   // ← required for unique_ptr and make_unique
using namespace std;

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
	// unique_ptr — same concept as raw pointer, auto-cleanup
	// --------------------------------------------------------
	// vector<unique_ptr<Vehicle>> works identically to
	// vector<Vehicle*> for polymorphism and the -> operator.
	//
	// The difference is ownership:
	// unique_ptr = "I am the ONE owner of this object"
	// When the unique_ptr is destroyed, it deletes the object.
	// When the vector is cleared, all unique_ptrs are destroyed.
	// Memory is freed automatically. No delete loop needed.
	// --------------------------------------------------------
	vector<unique_ptr<Vehicle>> swarm;
};
