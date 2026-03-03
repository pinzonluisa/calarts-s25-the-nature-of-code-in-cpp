//
//  particle.hpp
//  S26_NOC_05-01_ParticleSystems
//
//  Created by Luisa Pinzon
//

#ifndef particle_hpp
#define particle_hpp

#include "ofMain.h"

class Particle {
public:
    Particle();
    
    void setup(float orbitRadius, float startAngle);
    void applyForce(ofVec2f force);
    void update(float pullStrength, float pushStrength);
    void display();
    
    bool isDead();
    void respawn();
    
    // Cartesian
    ofVec2f position;
    ofVec2f velocity;
    ofVec2f acceleration;
    
    // Polar
    float r;
    float theta;
    float angularVelocity;
    
    // Properties
    float mass;
    float lifespan;
    ofColor particleColor;
};

#endif
