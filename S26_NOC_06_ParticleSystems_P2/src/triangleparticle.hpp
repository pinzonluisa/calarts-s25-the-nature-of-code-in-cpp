//
//  triangleparticle.hpp
//  S26_NOC_06_ParticleSystems_P2
//
//  Created by Luisa Pinzon on 3/14/26.

//  TRIANGLE PARTICLE (Derived Class)
//  ==================================
//  Inherits from Particle base class.
//
//  Shape: Triangle (3 sides)
//  Physics: BIGGER mass = more centrifugal force = floats outward
//  Respawn: Outer region of sphere (positive z, closer to viewer)
//

#ifndef triangleparticle_hpp
#define triangleparticle_hpp

#include "particle.hpp"

class TriangleParticle : public Particle {
	
public:
	
	TriangleParticle();
	
	void setup(float orbitRadius, float startAngle) override;
	void display() override;
	void respawn() override;
	
	// Note: We don't override update() anymore!
	// The bigger mass naturally creates more centrifugal push
};

#endif
