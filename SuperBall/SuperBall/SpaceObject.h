#include "Point2D.h"
#include <list>

#pragma once

class SpaceObject
{
public:
	SpaceObject(void);
	SpaceObject(float x, float y);   //@param: the position of the center 
	SpaceObject(float x, float y, double scoreForThePayer);
	~SpaceObject(void);

	float posX();
	float posY();
	void setNewPositionAndUpdateTheIntersectionPoints(float x, float y, Vector2D movement);

	virtual void SpaceObject::drawIt();  //called from the main loop

	double SpaceObject::getTheScoreForThePlayer();
	void SpaceObject::changeTheScoreForThePlayerTo(double score);

	std::list<Point2D> SpaceObject::getThePointsCountingForTheIntersections();

	

protected:
	float x,y;
	float width, height;
	double scoreForThePayer;
	std::list<Point2D> pointsCountingForAnIntersection;

private:
	//should be called in the constructor of the derived classes (if we have some static points counting for the intersections)
	virtual void buildThePointsCountingForTheIntersection() = 0; // = 0 signifie "virtuelle pure"
	
};

