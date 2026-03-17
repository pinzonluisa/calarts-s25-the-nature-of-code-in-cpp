//
//  emitter.hpp
//  S26_NOC_06_ParticleSystems_P2
//
//  Created by Luisa Pinzon on 3/14/26.

//  EMITTER CLASS
//  =============
//  Manages all particle types. Creates, updates, and displays them.
//
//  WHY SEPARATE VECTORS?
//  ---------------------
//  We have 4 vectors, one for each particle type:
//  • vector<CircleParticle> circles
//  • vector<TriangleParticle> triangles
//  • vector<HexagonParticle> hexagons
//  • vector<OctagonParticle> octagons
//
//  This is simpler than using pointers (which we'll learn in Autonomous Agents).
//  The tradeoff: more code to manage, but easier to understand.
//

#ifndef emitter_hpp
#define emitter_hpp

#include "ofMain.h"
#include "circleparticle.hpp"
#include "octagonparticle.hpp"
#include "attractor.hpp"

class Emitter {
	
public:
	
	Emitter();
	
	// Setup creates particles - divides numParticles among all types
	void setup(int numParticles);
	
	// Apply attractor force to all particles
	void applyAttractor(Attractor& attractor);
	
	// Update and display all particles
	void run(float pullStrength, float pushStrength);
	
	// Get total particle count (for display)
	int getTotalCount();
	
	// --------------------------------------------------------
	// SEPARATE VECTORS FOR EACH PARTICLE TYPE
	// --------------------------------------------------------
	// Each vector holds particles of one specific type.
	// This avoids the need for pointers while still allowing
	// different behaviors per type.
	
	vector<CircleParticle> circles;
	vector<OctagonParticle> octagons;
};

#endif
