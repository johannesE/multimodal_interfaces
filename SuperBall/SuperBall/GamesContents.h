#include "Diamond.h"
#include "SpaceObject.h"
#include "Mine.h"
#include <list>



#pragma once




class GamesContents
{
public:
	GamesContents(int screenWidth, int screenHeight, int initialNumberOfDiamonds, int initialNumberOfMines, float superBallSPositionX, float superBallSPositionY, float securityRadiusAroundTheCenterOfTheSuperBall);
	~GamesContents(void);


	void destroyTheObjectsAndAddThemToTheScore(std::list<SpaceObject*>);

	/*
	@return: Returns true iff there is a mine among the objects (classname Mine)
	*/
	bool checkForMines(std::list<SpaceObject*>);
	void addOneRandomDiamond();
	void addOneMine(float superBallSPositionX, float superBallSPositionY, float securityRadiusAroundTheCenterOfTheSuperBall);

	std::list<Diamond*> diamonds;
	int numberOfDiamonds;

	std::list<Mine*> mines;

	double playersScore;
	char playersScoreAsString[100];

private:
	void addToTheScore(SpaceObject* o);

	void destroy(SpaceObject* spo);

	int screenWidth, screenHeight;
};

