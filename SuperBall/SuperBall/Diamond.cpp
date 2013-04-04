#include "Diamond.h"
#include "glut.h"



Diamond::Diamond() : SpaceObject() { 	width=26;height=55;buildThePointsCountingForTheIntersection(); }

Diamond::Diamond(float x, float y) : SpaceObject(x,y) {	width=26;height=55;buildThePointsCountingForTheIntersection(); }

Diamond::Diamond(float x, float y, double scoreForThePlayer) : SpaceObject(x,y,scoreForThePlayer) {	width=26;height=55;buildThePointsCountingForTheIntersection(); }



Diamond::~Diamond(void)
{
	
}



void Diamond::drawIt() 
{



    glBegin(GL_TRIANGLES);

		GLfloat color[3] = {0.77647,1,0.94902};
		glColor3fv(color);
		glVertex3f(SpaceObject::x-width/2, y ,0);
		glVertex3f(x-width/2 + width/6, y ,0);
		glVertex3f(x, y-height/2 ,0);

		GLfloat color2[3] = {0.305882, 0.929412,1};
		glColor3fv(color2);
		glVertex3f(x-width/2 + width/6, y ,0);
		glVertex3f(x, y ,0);
		glVertex3f(x, y-height/2 ,0);

		GLfloat color3[3] = {0, 0.780392, 1};
		glColor3fv(color3);
		glVertex3f(x, y ,0);
		glVertex3f(x + 2*width/6, y ,0);
		glVertex3f(x, y-height/2 ,0);
	
		GLfloat color4[3] = {0, 0.552941, 0.898039};
		glColor3fv(color4);
		glVertex3f(x + 2*width/6, y ,0);
		glVertex3f(x + width/2, y ,0);
		glVertex3f(x, y-height/2 ,0);

		GLfloat color5[3] = {0,1,0.01098};
		glColor3fv(color5);
		glVertex3f(x-width/2 + width/6, y ,0);
		glVertex3f(x - width/2, y ,0);
		glVertex3f(x, y+height/2 ,0);

		GLfloat color6[3] = {0, 0.792157, 0.898039};
		glColor3fv(color6);
		glVertex3f(x, y ,0);
		glVertex3f(x-width/2 + width/6, y ,0);
		glVertex3f(x, y+height/2 ,0);

		GLfloat color7[3] = {0.117647, 0.52941176, 1};
		glColor3fv(color7);
		glVertex3f(x+width/2 - width/6, y ,0);
		glVertex3f(x, y ,0);
		glVertex3f(x, y+height/2 ,0);

		GLfloat color8[3] = {0.156863, 0.31372549, 1};
		glColor3fv(color8);
		glVertex3f(x+width/2, y ,0);
		glVertex3f(x+width/2 - width/6, y ,0);
		glVertex3f(x, y+height/2 ,0);

    glEnd();
}


//God save our gratest Queen, la la la la la la la la la la

void Diamond::buildThePointsCountingForTheIntersection()
{
	float width_6 = width/6.0f;
	float height_6 = height/6.0f;

	float width_4 = width/4.0f;
	float height_4 = height/4.0f;

	pointsCountingForAnIntersection.push_back( Point2D(x,y) );

	pointsCountingForAnIntersection.push_back( Point2D(x-width/2,y) );
	pointsCountingForAnIntersection.push_back( Point2D(x-2*width_6,y-height_6) );
	pointsCountingForAnIntersection.push_back( Point2D(x-width_6,y-2*height_6) );
	pointsCountingForAnIntersection.push_back( Point2D(x,y-height/2) );
	pointsCountingForAnIntersection.push_back( Point2D(x+width_6,y-2*height_6) );
	pointsCountingForAnIntersection.push_back( Point2D(x+2*width_6,y-height_6) );
	pointsCountingForAnIntersection.push_back( Point2D(x+width/2,y) );
	pointsCountingForAnIntersection.push_back( Point2D(x+2*width_6,y+height_6) );
	pointsCountingForAnIntersection.push_back( Point2D(x+width_6,y+2*height_6) );
	pointsCountingForAnIntersection.push_back( Point2D(x,y+height/2) );
	pointsCountingForAnIntersection.push_back( Point2D(x-width_6,y+2*height_6) );
	pointsCountingForAnIntersection.push_back( Point2D(x-2*width_6,y+height_6) );

	pointsCountingForAnIntersection.push_back( Point2D(x-width_4,y-height_4) );
	pointsCountingForAnIntersection.push_back( Point2D(x+width_4,y-height_4) );
	pointsCountingForAnIntersection.push_back( Point2D(x+width_4,y+height_4) );
	pointsCountingForAnIntersection.push_back( Point2D(x-width_4,y+height_4) );

}