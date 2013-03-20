#pragma once
#include "objects.h"


class Bomb :
	public Objects
{
public:
	Bomb(int x, int y);
	~Bomb(void);
	void draw();


private:
	// int x,y; the position of the bomb if the inheritance doesn't work


};

