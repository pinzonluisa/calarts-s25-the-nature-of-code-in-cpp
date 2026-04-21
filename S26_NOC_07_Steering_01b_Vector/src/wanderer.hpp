//
//  wanderer.hpp
//  S26_NOC_07_Steering_01b_Vector
//
//  Created by Luisa Pinzon
//
// ============================================================
//  WANDERER — derived from Vehicle
// ============================================================
//
//  Wanders randomly using a projected circle in front of it.
//  Draws as a CYAN circle instead of a triangle.
//
//  The wander algorithm:
//  1. Project an invisible circle ahead of the vehicle
//  2. Pick a random point on that circle each frame
//  3. Seek that point
//  Result: smooth, organic wandering motion
//

#pragma once
#include "vehicle.hpp"

class Wanderer : public Vehicle {
public:
	Wanderer(float x, float y);

	void update() override;  // different steering: wander instead of seek
	void draw()   override;  // draws cyan circle

private:
	float wanderAngle;       // current angle on the wander circle
							 // this is the EXTRA data a Wanderer has
							 // that a plain Vehicle does NOT
							 // → object slicing will destroy this
};
