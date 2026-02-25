//
//  mover.cpp
//  S25_NOC_05_OrbitalMotion
//
//  Created by Luisa Pinzon
//

#include "mover.hpp"

Mover::Mover() {
    
}

//--------------------------------------------------------------
void Mover::setup(float orbitRadius, float startAngle) {
    // Default mass (will be overwritten by slider in update)
    mass = 2.0;
    
    // ============================================
    // OLD: Random Cartesian position
    // ============================================
    // position = ofVec2f(ofRandom(width), ofRandom(height));
    // velocity = ofVec2f(ofRandom(-2, 2), ofRandom(-2, 2));
    
    // ============================================
    // NEW: Polar coordinates for orbital placement
    // ============================================
    // r IS the distance from center!
    // When r = 100, mover is 100 pixels from center
    // When r = 200, mover is 200 pixels from center
    
    r = orbitRadius;
    theta = startAngle;
    
    // Angular velocity: how fast to orbit
    // Closer objects orbit faster (Kepler's law)
    // angularVelocity = constant / r
    // Small r = large angularVelocity = fast orbit
    // Large r = small angularVelocity = slow orbit
    angularVelocity = 2.0 / r;
    
    // Calculate initial Cartesian position from polar
    position.x = r * cos(theta);
    position.y = r * sin(theta);
    
    velocity = ofVec2f(0, 0);
    acceleration = ofVec2f(0, 0);
}

//--------------------------------------------------------------
void Mover::applyForce(ofVec2f force) {
    // Newton's second law: A = F / M
    ofVec2f a = force / mass;
    acceleration += a;
}

//--------------------------------------------------------------
void Mover::update(bool enablePull, float pullStrength, float pushStrength) {
    // ============================================
    // ANGULAR MOTION (the orbit)
    // ============================================
	// Recalculate angular velocity based on CURRENT r
	angularVelocity = 2.0 / r;
	
    // theta = angle (position on the orbit)
    // angularVelocity = how fast the angle changes
    // Every frame we add angularVelocity to theta
    // This rotates the mover around the center
    // ============================================

    
    theta += angularVelocity;
    
    // ============================================
    // GRAVITATIONAL EFFECTS ON ORBITAL RADIUS
    // ============================================
    // Remember: r IS the distance from center!
    // Decreasing r = mover gets closer to center
    // Increasing r = mover gets farther from center
    //
    // Two forces fight each other:
    // 1. GRAVITY pulls inward (decreases r)
    // 2. CENTRIFUGAL pushes outward (increases r)
    // ============================================
    
    if (enablePull) {
        // ----- GRAVITATIONAL PULL (inward) -----
        // Uses the acceleration from attractor.attract()
        // Decreases r = pulls mover closer to center
		float gravitationalPull = acceleration.length();
        r -= gravitationalPull * pullStrength;
        
        // ----- CENTRIFUGAL PUSH (outward) -----
        // Real physics formula: F = m × ω² × r
        // Where:
        //   m = mass
        //   ω = angular velocity (omega)
        //   r = radius (distance from center)
        //
        // The * 20 is an arbitrary scale to make it
        // comparable in strength to the gravitational pull.
        // Without it, the push would be too weak to notice.
        float centrifugalPush = mass * angularVelocity * angularVelocity * r * 20;
        r += centrifugalPush * pushStrength;
    }
    
    // ----- CONSTRAIN r -----
	//constrain the position of movers
    r = ofClamp(r, 3, 500);
    
    // ============================================
    // CONVERT POLAR TO CARTESIAN
    // ============================================
    // We think in polar (r, θ) but we draw in Cartesian (x, y)
    //
    //    x = r × cos(θ)
    //    y = r × sin(θ)
    //
    // Since r is clamped above, position will be constrained too.
    // ============================================
    
    // OLD: Position updated by velocity
    // velocity += acceleration;
    // position += velocity;
    
    // NEW: Position calculated from polar coordinates
    position.x = r * cos(theta);
    position.y = r * sin(theta);
    
    // Clear acceleration each frame (same as before)
    acceleration *= 0;
}

//--------------------------------------------------------------
void Mover::display() {
    ofSetColor(127, 200);
    ofFill();
    
    // Size based on mass
    // sqrt(mass) = area-proportional sizing (physically accurate)
    // * 8 = arbitrary scale to make circles visible on screen
    //       You could use * 5 or * 12 — whatever looks good!
    float radius = sqrt(mass) * 8;
    ofDrawCircle(position.x, position.y, radius);
}
