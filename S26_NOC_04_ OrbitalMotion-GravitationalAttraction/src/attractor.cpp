//
//  attractor.cpp
//  S25_NOC_05_OrbitalMotion
//
//  Created by Luisa Pinzon
//

#include "attractor.hpp"

Attractor::Attractor() {
    
}

//--------------------------------------------------------------
void Attractor::setup(float x, float y, float m) {
    position = ofVec2f(x, y);
    mass = m;
    G = 1.0;
}

//--------------------------------------------------------------
ofVec2f Attractor::attract(const Mover& mover) {
    // ============================================
    // GRAVITATIONAL ATTRACTION
    // ============================================
    // Same formula as before: F = G × m1 × m2 / d²
    // The only change is Mover& instead of Mover (reference vs copy)
    // ============================================
    
    // Step 1: Get direction (vector pointing from mover to attractor)
    ofVec2f direction = position - mover.position;
    
    // Step 2: Get distance
    float distance = direction.length();// This should be the same as r
	
	distance = ofClamp(distance, 5, 25); // separate clamp for force
    
    // Step 3: Constrain distance
    // ============================================
    // WHY ONLY A MINIMUM?
    // ============================================
    // We use max() to ensure distance is at least 20.
    // 
    // max(a, b) returns the larger value:
    //   max(100, 20) = 100  (distance stays 100)
    //   max(5, 20) = 20     (distance becomes 20)
    //
    // This prevents very small distances because:
    //   strength = (G * m1 * m2) / (distance * distance)
    //
    // If distance is tiny (like 0.001):
    //   distance * distance = 0.000001
    //   Dividing by 0.000001 = HUGE force (or crash!)
    //
    // We don't need a maximum because:
    //   - Large distance = weak force (harmless)
    //   - r is already clamped in mover, so distance can't exceed 350
    //
    // OLD: Clamped both min and max
    // distance = ofClamp(distance, 5, 25);
    //
    // NEW: Just prevent getting too close
    // The 20.0f matches the minimum r clamp in mover.cpp
    // ============================================
    
    
    // Step 4: Calculate force magnitude using gravity formula
    float strength = (G * mass * mover.mass) / (distance * distance);
    
    // Step 5: Create force vector (direction × magnitude)
    direction.normalize();
    ofVec2f force = direction * strength;
    
    return force;
}

//--------------------------------------------------------------
void Attractor::display() {
    ofSetColor(100);
    ofFill();
    
    // Size based on mass (same sqrt approach as mover)
    float radius = sqrt(mass) * 2;
    ofDrawCircle(position.x, position.y, radius);
}
