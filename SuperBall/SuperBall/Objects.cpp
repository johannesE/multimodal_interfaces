#include "Objects.h"
#include "glut.h"


Objects objecttype;
//this class is the superclass for the diamonds and the bombs and eventually more objects.
//The type of the subclass should be defined using an enumeration.
Objects::Objects(void)
{
}


Objects::~Objects(void)
{
}

void Objects::setNewPos(int x, int y)
{
	this->x=x;
	this->y=y;
}

int Objects::getposX(){
	return this ->x;
}
int Objects::getposY(){
	return this ->y;
}