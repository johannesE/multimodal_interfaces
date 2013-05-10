#include "Diamond.h"
#include "SpaceObject.h"
#include "Mine.h"
#include <list>


#pragma once

#include <d2d1.h>

//for the speech
enum BallAction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
	STOP,
    NONE
};



//it must be static so that it can interact with the rest of the C program
class SuperBall
{
public:
	SuperBall(void);
	~SuperBall(void);
	static void SuperBall::speechAction(BallAction);

	//static void update_aX(int newValue, int zeroLevel, float divisor, float intervalOfToleranceAroundZero);
	//static void update_aY(int newValue, int zeroLevel, float divisor, float intervalOfToleranceAroundZero);

	static void update_vX(int newValue);
	static void update_vY(int newValue);
	static void updateRadius(int newValue);

	static std::list<SpaceObject*> getTheObjectsThatTheSuperBallIntersectsNow(std::list<Diamond*> diamonds, std::list<Mine*> mines);


	
};








