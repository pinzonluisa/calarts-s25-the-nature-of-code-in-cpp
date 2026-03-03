//
//  particle.cpp
//  S25_NOC_06_ParticleSystem
//
//  Created by Luisa Pinzon
//

#include "particle.hpp"

Particle::Particle() {
    
}

//--------------------------------------------------------------
void Particle::setup(float orbitRadius, float startAngle) {
    mass = ofRandom(1.0, 4.0);
    
    r = orbitRadius;
    theta = startAngle;
    angularVelocity = 2.0 / r;
    
    position.x = r * cos(theta);
    position.y = r * sin(theta);
    
    velocity = ofVec2f(0, 0);
    acceleration = ofVec2f(0, 0);
    
    lifespan = 255;
    
    // Color range: magenta to purple
    ofColor magenta = ofColor::fromHex(0xE0009D);
    ofColor purple = ofColor::fromHex(0x4F0BFF);
    particleColor = magenta.getLerped(purple, ofRandom(1.0));
}

//--------------------------------------------------------------
void Particle::applyForce(ofVec2f force) {
    ofVec2f a = force / mass;
    acceleration += a;
}

//--------------------------------------------------------------
void Particle::update(float pullStrength, float pushStrength) {
    angularVelocity = 2.0 / r;
    theta += angularVelocity;
    
    
	float gravitationalPull = acceleration.length();
	r -= gravitationalPull * pullStrength;
        
	float centrifugalPush = mass * angularVelocity * angularVelocity * r * 20;
	r += centrifugalPush * pushStrength;
    
    
    r = ofClamp(r, 3, 500);
    
    lifespan = ofMap(r, 10, 400, 20, 255, true);
    
    position.x = r * cos(theta);
    position.y = r * sin(theta);
    
    acceleration *= 0;
}

//--------------------------------------------------------------
bool Particle::isDead() {
    return r <= 40;
}

//--------------------------------------------------------------
void Particle::respawn() {
    r = ofRandom(350, 500);
    theta = ofRandom(TWO_PI);
    angularVelocity = 2.0 / r;
    lifespan = 255;
    
    ofColor magenta = ofColor::fromHex(0xE0009D);
    ofColor purple = ofColor::fromHex(0x4F0BFF);
    particleColor = magenta.getLerped(purple, ofRandom(1.0));
    
    position.x = r * cos(theta);
    position.y = r * sin(theta);
}

//--------------------------------------------------------------
void Particle::display() {
    ofSetColor(particleColor, lifespan);
    ofFill();
    
    float radius = sqrt(mass) * 5;
    ofDrawCircle(position.x, position.y, radius);
}
