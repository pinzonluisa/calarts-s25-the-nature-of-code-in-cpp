//
//  octagonparticle.hpp
//  S26_NOC_06_ParticleSystems_P2
//
//  Created by Luisa Pinzon on 3/14/26.

//  OCTAGON PARTICLE (Derived Class)
//  =================================
//  Inherits from Particle base class.
//
//  Shape: Octagon (8 sides)
//  Physics: OSCILLATES - bounces between inner and outer radius
//           Uses sin wave to create breathing/pulsing motion
//  Respawn: Equator of sphere (z near 0)
//

#ifndef octagonparticle_hpp
#define octagonparticle_hpp

#include "particle.hpp"

class OctagonParticle : public Particle {
	
public:
	
	OctagonParticle();
	
	void setup(float orbitRadius, float startAngle) override;
	void update(float pullStrength, float pushStrength) override;
	void display() override;
	void respawn() override;
	
private:
	// Octagon-specific: controls oscillation speed
	float oscillationSpeed;
};

#endif
