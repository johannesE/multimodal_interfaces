#include "SuperBall.h"



#include <time.h>
#include <math.h>
#include <string.h>
#include <stdlib.h> 

#include <glut.h>					// Override the definition of 'exit' in stdlib.h with that in glut.h. Place the stdlib.h line above the glut.h line in your code.



//Global variables:

GLsizei MOUSEx=0, MOUSEy=0;
GLfloat SIDE=200;
GLfloat BLUE[3] = {0,0,1};
GLfloat RED[3] = {1,0,0};


GLsizei x=100,y=100;
bool minusForDeltaX =false, minusForDeltaY = false;
typedef struct
{
float x;
float y;
}CIRCLE;


#define PI 3.14159265f
bool fullScreenMode = true;
int windowWidth, windowHeight,windowPosX, windowPosY, screenWidth, screenHeight;

int superBallSPositionX = 300;
int superBallSPositionY= 400;
float superBallSRadius = 80;


SuperBall::SuperBall()
{


	screenWidth = glutGet(GLUT_WINDOW_WIDTH);//glutGet(GLUT_SCREEN_WIDTH);
	screenHeight = glutGet(GLUT_WINDOW_HEIGHT);//glutGet(GLUT_SCREEN_HEIGHT);

	
	this->numberOfDiamonds=20;
	this->diamonds = new Diamond*[numberOfDiamonds];
	for(int i=0; i<numberOfDiamonds; i++)
	{
		int x = rand()%screenWidth;
		int y = rand()%screenHeight;
		this->diamonds[i] = new Diamond(x,y);
	}
}


SuperBall* superBall;





void drawSquare1()
{
    glColor3fv(BLUE);
    glBegin(GL_POLYGON);
        glVertex3f(MOUSEx, MOUSEy,0);
        glVertex3f(MOUSEx+SIDE, MOUSEy,0);
        glVertex3f(MOUSEx+SIDE, MOUSEy+SIDE,0);
        glVertex3f(MOUSEx, MOUSEy+SIDE,0);
    glEnd();


	glColor3fv(RED);
    glBegin(GL_POLYGON);
        glVertex3f(x, y,0);
        glVertex3f(x+SIDE, y,0);
        glVertex3f(x+SIDE, y+SIDE,0);
        glVertex3f(x, y+SIDE,0);
    glEnd();


	  time_t timer;
	  struct tm y2k;
	  long seconds;

	  y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	  y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

	  time(&timer);  /* get current time; same as: timer = time(NULL)  */

	  seconds = (long) difftime(timer,mktime(&y2k));

	int deltaX = seconds%2;
	int deltaY = seconds%3;

	if(x>screenWidth - SIDE) minusForDeltaX = true;
	if(x<=0) minusForDeltaX = false;
	if(y>screenHeight - SIDE) minusForDeltaY = true;
	if(y<=0) minusForDeltaY = false;

	if(minusForDeltaX) x-=deltaX;
	else x+=deltaX;
	if(minusForDeltaY) y-=deltaY;
	else y+=deltaY;

	


    glFlush();
}   


void drawCircle (int x, int y, int r) 
{
	CIRCLE circle;

	GLfloat color[3] = {1.0f,0.55f,0.0f};
	glColor3fv( color );

    glBegin(GL_LINES);
    for (float i = 0.0f; i < 180.0f; i++)
    {
		circle.x =x+  r * cos(i);
		circle.y =y+ r * sin(i);
		glVertex3f(circle.x,circle.y,0);
    
		circle.x = x+  r * cos(i + 0.1);
		circle.y = y+ r * sin(i + 0.1);
		glVertex3f(circle.x,circle.y,0);
    }
    glEnd();
}

void drawDisc (int x, int y, float r, float colorR, float colorG, float colorB) 
{

	GLfloat color[3] = {colorR,colorG,colorB};
	glColor3fv( color );

    glBegin(GL_POLYGON);

    for (float i = 0.0f; i < 360.0f; i++)
    {
		glVertex3f(x +  r * cos(i), y + r * sin(i),0);
    }

    glEnd();
}




void display(void)
{   
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity(); 

	//-----------------------
    drawSquare1();
	drawCircle (600, 300, 100);
	drawDisc (superBallSPositionX, superBallSPositionY, superBallSRadius, 1.0f, 0.6f, 0.05f);
	drawCircle (300, 400, 10);
	for(int i=0; i<superBall->numberOfDiamonds; i++)
	{
		((superBall->diamonds)[i])->drawIt();
	}
	glutSwapBuffers();
}





void reshape(int w, int h)
{   
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
     //gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);

    //glOrtho(0.0,1368,768,0,-1.0,1.0);
	glOrtho(0.0, glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT), 0.0, -1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void spindisplay(void)
{       
    glutPostRedisplay();
}

void setX(int x)
{
    MOUSEx=x;
}

void setY(int y)
{
    MOUSEy=y;
}

void mouse(int btn, int state, int x, int y)
{
	/*
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)   
    {
        setX(x);
        setY(y);
        //drawSquare(MOUSEx,HEIGHT-MOUSEy);
        glutPostRedisplay();
    }
	*/


	setX(x);
    setY(y);
	glutPostRedisplay();


    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)   
    {
        exit(1);
    }
}

void specialKeys(int key, int x, int y) 
{
   switch (key) {
		case GLUT_KEY_F11:    // F11: Toggle between full-screen and windowed mode
			fullScreenMode = !fullScreenMode;         
			if (fullScreenMode) 
			{                     
				windowPosX   = glutGet(GLUT_WINDOW_X); 
				windowPosY   = glutGet(GLUT_WINDOW_Y);
				windowWidth  = glutGet(GLUT_WINDOW_WIDTH);
				windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
				
				glutFullScreen();                      
			} 
			else 
			{                                        
				if(windowWidth<=0) windowWidth = 800;
				if(windowHeight<=0) windowHeight = 500;
				if(windowPosX<=0) windowPosX = 300;
				if(windowPosY<=0) windowPosY = 100;
				glutReshapeWindow(windowWidth,windowHeight); 
				glutPositionWindow(windowPosX,windowPosY);   
			}
		break;
		case 27:   //Escape key
			fullScreenMode = false;
			if(windowWidth<=0) windowWidth = 800;
			if(windowHeight<=0) windowHeight = 500;
			if(windowPosX<=0) windowPosX = 300;
			if(windowPosY<=0) windowPosY = 100;
			glutReshapeWindow(windowWidth,windowHeight); 
			glutPositionWindow(windowPosX,windowPosY);
		break;

		//37(left arrow); 38(up arrow); 39(right arrow); 40(down arrow)
		case 37:
			superBallSPositionX--;
		break;
		case 38:
			superBallSPositionY--;
		break;
		case 39:
			superBallSPositionX++;
		break;
		case 40:
			superBallSPositionY++;
		break;
		glutPostRedisplay();
   }
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
		case 27:   //Escape key
			fullScreenMode = false;
			glutReshapeWindow(windowWidth,windowHeight); 
			glutPositionWindow(windowPosX,windowPosY);
		break;
		
  }
}


int main(int argc, char **argv)
{   
	
	

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize( glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT) );
    glutInitWindowPosition(400,150);
	  
	char* s = "Super Ball";
    glutCreateWindow(s);
	glutFullScreen(); 
	superBall = new SuperBall();


    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutIdleFunc(spindisplay);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);
    glutMainLoop();
}