//
//  walker.hpp
//  S25_NOC_01_RandomWalker
//
//  Created by Luisa Pinzon on 2/3/25
//

#ifndef walker_hpp
#define walker_hpp

#include <stdio.h>
#include "ofMain.h"

class walker {
public:
	walker();
	
	void setup();
	void update();
	void display(float r, float g, float b, float size);
	
	float x;
	float y;
};

#endif /* walker_hpp */
