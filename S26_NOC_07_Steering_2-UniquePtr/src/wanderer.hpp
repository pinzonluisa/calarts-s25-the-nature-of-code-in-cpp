
//  wanderer.hpp
//  S26_NOC_07_Steering_2_UniquePtr
//
//  Created by Luisa Pinzon
//
// ============================================================
//  WANDERER — ignores mouse, wanders freely, draws cyan
// ============================================================
//
//  This is the key class for showing why pointers matter.
//  It has EXTRA data (wanderAngle) that Vehicle doesn't have.
//  With vector<Vehicle> that data gets sliced off.
//  With vector<unique_ptr<Vehicle>> it's preserved.
//

#pragma once
#include "vehicle.hpp"

class Wanderer : public Vehicle {
public:
	Wanderer(float x, float y);

	// mouse parameter is received but intentionally ignored
	void update(ofVec2f mouse) override;
	void draw()                override;

private:
	float wanderAngle;  // ← extra data unique to Wanderer
						//   this is what slicing destroys
};				 // → object slicing will destroy this

