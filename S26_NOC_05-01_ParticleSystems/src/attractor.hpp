//
//  attractor.hpp
//  S25_NOC_06_ParticleSystem
//
//  Created by Luisa Pinzon
//

#ifndef attractor_hpp
#define attractor_hpp

#include "ofMain.h"
#include "particle.hpp"

class Attractor {
public:
    Attractor();
    
    void setup(float m);
    ofVec2f attract(const Particle& particle);
	
	ofVec2f velocity;
	void updatePosition(ofVec2f target, float easing);
    
    ofVec2f position;
    float mass;
    float G;
};

#endif
