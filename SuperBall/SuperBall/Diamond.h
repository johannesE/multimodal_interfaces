
#include "SpaceObject.h"
#pragma once



class Diamond:public SpaceObject
{

public:
	Diamond::Diamond();
	Diamond(float x, float y);
	Diamond(float x, float y, double scoreForThePlayer);
	~Diamond(void);
	void Diamond::drawIt();  //called from the main loop
	

	
	
private:
	
	void buildThePointsCountingForTheIntersection();
	
};

