#include "Mine.h"
#include <math.h>
#include <iostream>
#include <glut.h>	


#define PI2 6.283185307f
#define one_tenth_PI 0.31141592654f





Mine::Mine(float x, float y) : SpaceObject(x,y,0) 
{ 
	this->width = 30;
	this->height = 30;
	buildThePointsCountingForTheIntersection();
	randMovementVector = Vector2D(rand(), rand());
	randMovementVector *= normOfTheRandMovementVector/Magnitude(randMovementVector);
}

Mine::Mine(float x, float y, double scoreForThePlayer) : SpaceObject(x,y,scoreForThePlayer) 
{ 
	this->width = 30;
	this->height = 30;
	buildThePointsCountingForTheIntersection(); 
	randMovementVector = Vector2D(rand(), rand());
	randMovementVector *= normOfTheRandMovementVector/Magnitude(randMovementVector);
}


Mine::~Mine(void)
{
}


void Mine::drawIt()  //called from the main loop
{
	
	
	
	glBegin(GL_TRIANGLES);

		GLfloat color[3] = {0.0, 0.0, 0.0};
		glColor3fv(color);

		for(float a=0; a<PI2; a+=one_tenth_PI)
		{
			glTexCoord3f(x, y ,0);
			glVertex3f(x, y ,0);
			glTexCoord3f(x + cos(a), y-sin(a) ,0);
			glVertex3f(x + cos(a)*radius, y-sin(a)*radius ,0);
			glTexCoord3f(x + cos(a+one_tenth_PI), y-sin(a+one_tenth_PI),0);
			glVertex3f(x + cos(a+one_tenth_PI)*radius, y-sin(a+one_tenth_PI)*radius ,0);
		}
    glEnd();
	
}

void Mine::buildThePointsCountingForTheIntersection()
{
	//TODO: adapt to the image:
	for(float a=0; a<PI2; a+=one_tenth_PI)
		{
			pointsCountingForAnIntersection.push_back( Point2D(    (float)(x + cos(a)*radius), (float)(y-sin(a)*radius)   ));
		}
}


void Mine::updateTheRandMovementVector()
{

	int rand1 = rand()%100; if(rand1==0) rand1=1; //  in [1,..,99]
	int rand2 = rand()%100; if(rand2==0) rand2=1;//  in [1,..,99]
	float moins1ouPlus1_0_1;
	float moins1ouPlus1_0_2;
	if(rand()%2==1) moins1ouPlus1_0_1=0.1f; else moins1ouPlus1_0_1=-0.1f;
	if(rand()%2==1) moins1ouPlus1_0_2=0.1f; else moins1ouPlus1_0_2=-0.1f;

	this->randMovementVector += Vector2D( moins1ouPlus1_0_1 * (rand()%rand1), moins1ouPlus1_0_2 * (rand()%rand2) );
	this->randMovementVector *= normOfTheRandMovementVector/Magnitude(this->randMovementVector);
}

void Mine::setTheComponentYofTheRandomVectorNegative() {this->randMovementVector.y = (float) -1.0f*abs(this->randMovementVector.y); this->randMovementVector *= normOfTheRandMovementVector/Magnitude(this->randMovementVector);}
void Mine::setTheComponentYofTheRandomVectorPositive() {this->randMovementVector.y = (float) abs(this->randMovementVector.y); this->randMovementVector *= normOfTheRandMovementVector/Magnitude(this->randMovementVector);}
void Mine::setTheComponentXofTheRandomVectorNegative() {this->randMovementVector.x = (float) -1.0f*abs(this->randMovementVector.x); this->randMovementVector *= normOfTheRandMovementVector/Magnitude(this->randMovementVector);}
void Mine::setTheComponentXofTheRandomVectorPositive() {this->randMovementVector.x = (float) abs(this->randMovementVector.x); this->randMovementVector *= normOfTheRandMovementVector/Magnitude(this->randMovementVector);}