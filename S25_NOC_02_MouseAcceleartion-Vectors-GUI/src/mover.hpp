//
//  mover.hpp
//  S25_NOC_02_MouseAcceleartion-Vectors-GUI
//
//  Created by Luisa Pinzon on 2/9/26.
//

#ifndef mover_hpp
#define mover_hpp

#include <stdio.h>
#include "ofMain.h"

class mover {
public:
	mover();
	
	void setup();
	void update();
	void display();
	
	ofVec2f position;
	ofVec2f velocity;
	ofVec2f acceleration;
	float topSpeed;
};

#endif /* mover_hpp */
