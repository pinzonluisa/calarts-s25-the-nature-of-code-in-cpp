//
//  circleparticle.hpp
//  S26_NOC_06_ParticleSystems_P2
//
//  Created by Luisa Pinzon on 3/14/26.

//  CIRCLE PARTICLE (Derived Class)
//  ================================
//  Inherits from Particle base class.
//  This is the "baseline" particle - stable orbit, no special physics.
//
//  Shape: Smooth circle (32 sides)
//  Physics: Standard pull/push balance
//  Respawn: Anywhere on the sphere
//
//  KEY C++ CONCEPT: INHERITANCE
//  ----------------------------
//  The syntax ": public Particle" means:
//  • CircleParticle IS a Particle (has all its properties and methods)
//  • CircleParticle can ADD new features or OVERRIDE existing ones
//  • "public" inheritance means Particle's public members stay public
//

#ifndef circleparticle_hpp
#define circleparticle_hpp

#include "particle.hpp"

// ": public Particle" = CircleParticle inherits from Particle
class CircleParticle : public Particle {
	
public:
	
	// Constructor
	CircleParticle();
	
	// --------------------------------------------------------
	// OVERRIDE KEYWORD
	// --------------------------------------------------------
	// "override" tells the compiler: "I'm replacing a virtual method from parent"
	// If we misspell the method name, compiler will catch the error
	// Without override, a typo would create a NEW method instead of replacing
	
	void setup(float orbitRadius, float startAngle) override;
	void update(float pullStrength, float pushStrength) override;
	void display() override;
	void respawn() override;
};

#endif
