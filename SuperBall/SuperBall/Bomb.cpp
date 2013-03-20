#include "Bomb.h"
#include <iostream>


class Bomb : public Objects{ //the constructor defines the inheritance
public:
	Bomb(int x, int y) : Objects() { //the constructer Bomb(x,y) calls automatically Objects()
		this->x=x;
		this->y=y;

	}
};

