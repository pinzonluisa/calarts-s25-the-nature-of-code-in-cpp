//
//  emitter.cpp
//  S25_NOC_06_ParticleSystem
//
//  Created by Luisa Pinzon
//

#include "emitter.hpp"

Emitter::Emitter() {
    
}

//--------------------------------------------------------------
void Emitter::setup(int numParticles) {
    particles.clear();
    
    for (int i = 0; i < numParticles; i++) {
        Particle p;
        float orbitRadius = ofRandom(100, 450);
        float startAngle = ofRandom(TWO_PI);
        p.setup(orbitRadius, startAngle);
        particles.push_back(p);
    }
}

//--------------------------------------------------------------
void Emitter::applyAttractor(Attractor& attractor) {
    for (int i = 0; i < particles.size(); i++) {
        ofVec2f force = attractor.attract(particles[i]);
        particles[i].applyForce(force);
    }
}

//--------------------------------------------------------------
void Emitter::run(float pullStrength, float pushStrength) {
    // Loop backwards for safe removal/respawn
    for (int i = particles.size() - 1; i >= 0; i--) {
        particles[i].update(pullStrength, pushStrength);
        particles[i].display();
        
        if (particles[i].isDead()) {
            particles[i].respawn();
        }
    }
}
