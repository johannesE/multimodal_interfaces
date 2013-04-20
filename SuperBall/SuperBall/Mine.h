#include "SpaceObject.h"
#include <math.h>
#include "glut.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

#pragma once



class Mine : public SpaceObject
{
public:
	Mine(float x, float y);
	Mine(float x, float y, double scoreForThePlayer);
	~Mine(void);
	void Mine::drawIt();  //called from the main loop
	GLuint LoadTextureRAW( const char * filename, int wrap );



	void updateTheRandMovementVector();

	Vector2D randMovementVector;

	static const int normOfTheRandMovementVector = 50;    //The smaller it is, the more easilly this vector will change of direction (while adding some random numbers to it's components)

	void setTheComponentYofTheRandomVectorNegative();
	void setTheComponentYofTheRandomVectorPositive();
	void setTheComponentXofTheRandomVectorNegative();
	void setTheComponentXofTheRandomVectorPositive();
	
	

private:
	
	static const int radius=40;

	
	void Mine::buildThePointsCountingForTheIntersection();
};

