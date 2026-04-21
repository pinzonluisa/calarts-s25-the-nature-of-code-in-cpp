//
//  seeker.hpp
//  S26_NOC_07_Steering_01b_Vector
//
//  Created by Luisa Pinzon on 4/20/26.
//

// ============================================================
//  SEEKER — derived from Vehicle
// ============================================================
//
//  Seeks the mouse. Draws as a YELLOW triangle.
//  Identical steering to base Vehicle, different color.
//
//  KEY C++ SYNTAX:
//      class Seeker : public Vehicle
//      → Seeker IS a Vehicle, inherits everything from it
//

#pragma once
#include "vehicle.hpp"

class Seeker : public Vehicle {
public:
	Seeker(float x, float y);
	void draw() override;   // draws yellow — overrides base draw
};
