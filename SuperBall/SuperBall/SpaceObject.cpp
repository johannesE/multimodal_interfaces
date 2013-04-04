#include "SpaceObject.h"


SpaceObject::SpaceObject(void)
{
	this->x=150;
	this->y=100;
	this->scoreForThePayer=100;
	//buildThePointsCountingForTheIntersection();
}

///@Param: the position of the center
SpaceObject::SpaceObject(float x, float y)
{
	this->x=x;
	this->y=y;
	this->scoreForThePayer=100;
	//buildThePointsCountingForTheIntersection();
}
///@Param: the position of the center
SpaceObject::SpaceObject(float x, float y, double scoreForThePayer)
{
	this->x=x;
	this->y=y;
	this->scoreForThePayer=scoreForThePayer;
	//buildThePointsCountingForTheIntersection();
}

SpaceObject::~SpaceObject(void)
{
}

void SpaceObject::setNewPositionAndUpdateTheIntersectionPoints(float x, float y,Vector2D movement)
{
	this->x=x;
	this->y=y;
	if(!pointsCountingForAnIntersection.empty())
	{
		for (std::list<Point2D>::iterator it = pointsCountingForAnIntersection.begin(); it != pointsCountingForAnIntersection.end(); it++)
		{
			(*it) += movement;
		}
	}
}


float SpaceObject::posX()
{
	return this->x;
}
float SpaceObject::posY()
{
	return this->y;
}



double SpaceObject::getTheScoreForThePlayer()
{
	return this->scoreForThePayer;
}

void SpaceObject::changeTheScoreForThePlayerTo(double score)
{
	this->scoreForThePayer=score;
}

void SpaceObject::drawIt()  //called from the main loop
{
	//(not implemented for SpaceObject.)
}



std::list<Point2D> SpaceObject::getThePointsCountingForTheIntersections()
{
	return this->pointsCountingForAnIntersection;
}





