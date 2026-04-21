//
//  seeker.hpp
//  S26_NOC_07_Steering_2-UniquePtr
//
//  Created by Luisa Pinzon
//
// ============================================================
//  SEEKER — seeks the mouse, draws orange
// ============================================================

#pragma once
#include "vehicle.hpp"

class Seeker : public Vehicle {
public:
	Seeker(float x, float y);
	void update(ofVec2f mouse) override;
	void draw() override;
};
