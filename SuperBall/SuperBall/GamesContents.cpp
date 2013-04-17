#include "GamesContents.h"
#include <exception>

GamesContents::GamesContents(int screenWidth, int screenHeight, int initialNumberOfDiamonds, int initialNumberOfMines, float superBallSPositionX, float superBallSPositionY, float securityRadiusAroundTheCenterOfTheSuperBall)
{
	if(screenWidth<=0 || screenHeight<=0) throw int(41);

	this->screenWidth=screenWidth;
	this->screenHeight=screenHeight;
	this->numberOfDiamonds=initialNumberOfDiamonds;

	std::list<Diamond*> l;
	this->diamonds = l; //Diamond*[numberOfDiamonds];

	for(int i=0; i<numberOfDiamonds; i++)
	{
		int x = rand()%screenWidth;
		int y = rand()%screenHeight;
		this->diamonds.push_back( new Diamond(x,y));
	}

	std::list<Mine*> l2;
	this->mines = l2;
	for(int i=0; i<initialNumberOfMines; i++)
	{
		addOneMine(superBallSPositionX, superBallSPositionY, securityRadiusAroundTheCenterOfTheSuperBall);
	}

	playersScore = 0;
	for(int i=0; i<99; i++)
	{
		playersScoreAsString[i]=' ';
	}
	playersScoreAsString[99]='\0';

}

void GamesContents::addOneRandomDiamond()
{
	int x = rand()%screenWidth;
	int y = rand()%screenHeight;
	this->diamonds.push_back( new Diamond(x,y));
	this->numberOfDiamonds++;
}

void GamesContents::addOneMine(float superBallSPositionX, float superBallSPositionY, float securityRadiusAroundTheCenterOfTheSuperBall)
{
	float dist;
	int x,y;
	int tries=0;
	do
	{
		x = rand()%screenWidth;
		y = rand()%screenHeight;
		float dx=superBallSPositionX-x;
		float dy =superBallSPositionY-y;
		dist = sqrt(dx*dx + dy*dy);
		tries++;
	}
	while(dist < securityRadiusAroundTheCenterOfTheSuperBall && tries < 1000);
	if(tries>=1000) return;

	this->mines.push_back( new Mine(x,y));

}


GamesContents::~GamesContents(void)
{
}


void GamesContents::destroy(SpaceObject* spo)
{
	if( (typeid(*spo)) == typeid(Diamond) ) 
		{
			Diamond* d = (Diamond*)(spo);
			diamonds.remove(d);
		}
}


void GamesContents::addToTheScore(SpaceObject* spo)
{
	playersScore+= spo->getTheScoreForThePlayer();
}


void GamesContents::destroyTheObjectsAndAddThemToTheScore(std::list<SpaceObject*> l)
{
	for (std::list<SpaceObject*>::iterator it = l.begin(); it != l.end(); it++)
	{
		if( (typeid(**it)) == typeid(Diamond) ) 
		{
			Diamond* d = (Diamond*)(*it);
			
			addToTheScore(d);
			destroy(d);
		}
	}
}

/*
@return: Returns true iff there is a mine among the objects (classname Mine)
*/
bool GamesContents::checkForMines(std::list<SpaceObject*> l)
{
	for (std::list<SpaceObject*>::iterator it = l.begin(); it != l.end(); it++)
	{
		if( (typeid(**it)) == typeid(Mine) ) 
		{
			return true;
		}
	}
	return false;
}