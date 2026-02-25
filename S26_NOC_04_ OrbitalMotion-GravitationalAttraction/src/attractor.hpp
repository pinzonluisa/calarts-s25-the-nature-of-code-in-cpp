//
//  attractor.hpp
//  S25_NOC_05_OrbitalMotion
//
//  Created by Luisa Pinzon
//
//  ============================================
//  WHAT CHANGED:
//  ============================================
//  
//  BEFORE: attract(Mover mover)  -- made a COPY (slow)
//  NOW:    attract(Mover& mover) -- uses REFERENCE (fast)
//  
//  The & means "reference" — we work with the original object
//  instead of making a copy every frame.
//

#ifndef attractor_hpp
#define attractor_hpp

#include "ofMain.h"
#include "mover.hpp"

class Attractor {
public:
    Attractor();
    
    void setup(float x, float y, float m);
    
    // ============================================
    // OLD: Made a copy of mover (slow)
    // ============================================
    // ofVec2f attract(Mover mover);
    
    // ============================================
    // NEW: Uses reference (fast, no copy)
    // ============================================
    ofVec2f attract(const Mover& mover);
    
    void display();
    
    ofVec2f position;
    float mass;
    float G;  // Gravitational constant
};

#endif /* attractor_hpp */
