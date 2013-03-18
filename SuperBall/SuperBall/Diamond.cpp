#include "Diamond.h"
#include "glut.h"



Diamond::Diamond()
{
	this->x=150;
	this->y=100;
}

Diamond::Diamond(int x, int y)
{
	this->x=x;
	this->y=y;
}


Diamond::~Diamond(void)
{

}


void Diamond::setNewPos(int x, int y)
{
	this->x=x;
	this->y=y;
}


int Diamond::posX()
{
	return this->x;
}
int Diamond::posY()
{
	return this->y;
}

void Diamond::drawIt() 
{
	int width=26;
	int height=55;


    glBegin(GL_TRIANGLES);

		GLfloat color[3] = {0.77647,1,0.94902};
		glColor3fv(color);
		glVertex3f(x-width/2, y ,0);
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
