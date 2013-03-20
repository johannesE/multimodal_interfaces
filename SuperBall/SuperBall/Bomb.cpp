#include "Bomb.h"
#include <iostream>
#include "glut.h"

class Bomb : public Objects{ //the constructor defines the inheritance
public:
	Bomb(int x, int y) : Objects() { //the constructer Bomb(x,y) calls automatically Objects()
		this->x=x;
		this->y=y;
		this->width = 30;
		this->height = 30;

	}

	void draw(){
		glBegin(GL_TRIANGLES); //idea: draw two triangles and add a shader as the image

		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(x, y, 0);
		glVertex3f(x+width, y, 0);
		glVertex3f(x,y+height, 0);

		glVertex3f(x+width, y+height, 0);
		glVertex3f(x+width, y, 0);
		glVertex3f(x,y+height, 0);



		glEnd();

	}
	
};



