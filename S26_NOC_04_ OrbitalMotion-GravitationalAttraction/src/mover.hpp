//
//  mover.hpp
//  S25_NOC_05_OrbitalMotion
//
//  Created by Luisa Pinzon
//
//  ============================================
//  WHAT CHANGED FROM BASIC GRAVITATIONAL ATTRACTION:
//  ============================================
//  
//  BEFORE (Linear Motion):
//      - Position was (x, y) Cartesian coordinates
//      - Velocity moved position directly
//      - Movers flew around chaotically
//  
//  NOW (Orbital Motion):
//      - Position is calculated from POLAR coordinates (r, θ)
//      - Angular velocity rotates the mover around center
//      - Gravity affects orbital radius (r), not position directly
//      - Movers orbit like planets around a sun
//  
//  KEY CONCEPT: r IS the distance!
//      r = distance from center (orbital radius)
//      θ (theta) = angle around center
//      x = r × cos(θ)
//      y = r × sin(θ)
//
//  When r = 100, mover is 100 pixels from center.
//  When r = 200, mover is 200 pixels from center.
//  Changing r changes the orbital distance!
//

#ifndef mover_hpp
#define mover_hpp

#include "ofMain.h"

class Mover {
public:
    Mover();
    
    void setup(float orbitRadius, float startAngle);
    void applyForce(ofVec2f force);
    void update(bool enablePull, float pullStrength, float pushStrength);
    void display();
    
    // ============================================
    // OLD: Just Cartesian coordinates
    // ============================================
    // ofVec2f position;
    // ofVec2f velocity;
    // ofVec2f acceleration;
    // float mass;
    
    // ============================================
    // NEW: Polar + Cartesian
    // ============================================
    
    // ----- CARTESIAN (for drawing) -----
    ofVec2f position;      // Final screen position (calculated from r and theta)
    ofVec2f velocity;      // (not used for movement anymore, kept for compatibility)
    ofVec2f acceleration;  // Gravitational acceleration (affects r now, not position)
    
    // ----- POLAR (for orbital motion) -----
    float r;               // Orbital radius = distance from center
    float theta;           // Current angle (position along orbit)
    float angularVelocity; // How fast the mover rotates around center
    
    // ----- PROPERTIES -----
    float mass;
};

#endif /* mover_hpp */
