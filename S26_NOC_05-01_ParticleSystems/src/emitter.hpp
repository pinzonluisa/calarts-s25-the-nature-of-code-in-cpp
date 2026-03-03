//
//  emitter.hpp
//  S25_NOC_06_ParticleSystem
//
//  Created by Luisa Pinzon
//

#ifndef emitter_hpp
#define emitter_hpp

#include "ofMain.h"
#include "particle.hpp"
#include "attractor.hpp"

class Emitter {
public:
    Emitter();
    
    void setup(int numParticles);
    void applyAttractor(Attractor& attractor);
    void run(float pullStrength, float pushStrength);
    
    vector<Particle> particles;
};

#endif
