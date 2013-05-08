#include "SuperBall.h"

#include <time.h>
#include "SuperBall.h"
#include <math.h>
#include <string.h>
#include <stdio.h> //for the Phidgets
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <glut.h> // Override the definition of 'exit' in stdlib.h with that in glut.h. Place the stdlib.h line above the glut.h line in your code.
#include <phidget21.h> //for the Phidgets

#include "PhidgetManager.h"

#include <list>
#include <typeinfo>
#include "GamesContents.h"
#include "Point2D.h"
#include "texture2.h"

<<<<<<< HEAD
#include "stdafx.h"
#include <NuiApi.h>
=======


>>>>>>> 8c0a3bd7bba0039ce8e85d5b98d1c188bee5a398




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
#define PI2 6.283185307f
#define one_fifteenth_PI 0.20943951f
#define e 2.71828182846
#define e_pw2 7.38905609893
bool fullScreenMode = true;
int windowWidth, windowHeight,windowPosX, windowPosY, screenWidth, screenHeight;

int superBallSPositionX = 300;
int superBallSPositionY= 400;
float superBallSRadius = 50;
float superBallSRadiusMin = 40;
float superBallSRadiusMax = 150;
float superBallSSpeedX = 0.0f;
float superBallSSpeedY = 0.0f;
float superBallSAX = 0.0f;
float superBallSAY = 0.0f;
GLfloat superBallsColor[3] = {1.0f, 0.5f, 0.0f};
GLfloat openglClearColor[4] = {0.760784313,0.839215686,0.839215686,1.0};
GLfloat bombsColor[3] = {0.0f, 0.0f, 0.0f};
GLfloat colorOfTheScore[3] = {1.0f, 0.0078f, 0.41960784f};

PhidgetManager* phidgetManag;
GamesContents* gamesContents;

float sensor1and2zeroLevel = 500;
double sensor1and2SizeOfTheValuesArea = 500.0; //we can at maximum add or remove this value to/from the zero level. With this we have the whole spectrum.
double sensor1and2finalValueDivisor = 4.5;
float sensor1and2firstToleranceIntervalAroundTheZeroValue = 40.0f;


unsigned int milliSecondsIntervalForSpawningNewSpaceObjects = 2000;
//unsigned int milliSecondsIntervalForMovingTheBombs =50;

float bombsAttractionFactor = 0.17f;
float bombsFactorForThierIndependentRandomMovement = 0.17f; //should be more or less the double of the attraction, or something like that

bool gameOver = false;

//for the speed
int ballSpeed = 5;
bool ismoving = false;

GLuint texture_bomb;
GLubyte* imageData;

//for the game over
int ButtonX = 50;
int ButtonY = 50;
int ButtonHEIGHT = 100;
int ButtonWIDTH = 200;


void SuperBall::speechAction(BallAction bAction){
	switch(bAction){
	case UP :
		ismoving = true;
		while(ismoving){
			superBallSPositionY-=10*ballSpeed;
		}
		break;
	case DOWN:
		superBallSPositionY+=10*ballSpeed;
		break;
	case LEFT:
		superBallSPositionX-=10*ballSpeed;
		break;
	case RIGHT:
		superBallSPositionX+=10*ballSpeed;
		break;
	case NONE:
		ismoving = false;


	}
}

SuperBall::SuperBall()
{

}

SuperBall::~SuperBall()
{
}
/*
void SuperBall::update_aX(int newValue, int zeroLevel, float divisor, float intervalOfToleranceAroundZero)
{
if((zeroLevel-intervalOfToleranceAroundZero)<newValue && (zeroLevel+intervalOfToleranceAroundZero)>newValue) superBallSAX=0.0f;
else superBallSAX = (newValue-zeroLevel)/divisor;
}
void SuperBall::update_aY(int newValue, int zeroLevel, float divisor, float intervalOfToleranceAroundZero)
{
if((zeroLevel-intervalOfToleranceAroundZero)<newValue && (zeroLevel+intervalOfToleranceAroundZero)>newValue) superBallSAY=0.0f;
else superBallSAY = (newValue-zeroLevel)/divisor;

}*/
void SuperBall::update_vX(int newValue)
{
if((sensor1and2zeroLevel-sensor1and2firstToleranceIntervalAroundTheZeroValue)<newValue && (sensor1and2zeroLevel+sensor1and2firstToleranceIntervalAroundTheZeroValue)>newValue) { superBallSSpeedX=0.0f; return;}


int sign;
if(abs(newValue-sensor1and2zeroLevel) == newValue-sensor1and2zeroLevel)
{
sign = 1;
}
else
{
sign=-1;
}
double x1 = (newValue-sensor1and2zeroLevel)/sensor1and2SizeOfTheValuesArea * sign * 2.0; //between 0 and 2

double x2 = exp(x1); //between 1 and e^2 = 7.389056099

double x3 = (x2-1)*100.0; //between 0 and (e^2-1)*100

double x4 = x3/(e_pw2-1)*sign; //between 0 and 100 , but moreover with a sign

superBallSSpeedX = -x4/sensor1and2finalValueDivisor;

}
void SuperBall::update_vY(int newValue)
{
if((sensor1and2zeroLevel-sensor1and2firstToleranceIntervalAroundTheZeroValue)<newValue && (sensor1and2zeroLevel+sensor1and2firstToleranceIntervalAroundTheZeroValue)>newValue) { superBallSSpeedY=0.0f; return;}


int sign;
if(abs(newValue-sensor1and2zeroLevel) == newValue-sensor1and2zeroLevel)
{
sign = 1;
}
else
{
sign=-1;
}
double x1 = (newValue-sensor1and2zeroLevel)/sensor1and2SizeOfTheValuesArea * sign * 2.0; //between 0 and 2

double x2 = exp(x1); //between 1 and e^2 = 7.389056099

double x3 = (x2-1)*100.0; //between 0 and (e^2-1)*100

double x4 = x3/(e_pw2-1)*sign; //between 0 and 100 , but moreover with a sign

superBallSSpeedY = -x4/sensor1and2finalValueDivisor;
}
void SuperBall::updateRadius(int newValue)
{
superBallSRadius = newValue / 1000.0 *(superBallSRadiusMax-superBallSRadiusMin) + superBallSRadiusMin;
}

std::list<SpaceObject*> SuperBall::getTheObjectsThatTheSuperBallIntersectsNow(std::list<Diamond*> diamonds, std::list<Mine*> mines)
{
std::list<SpaceObject*> listeResultante;

for (std::list<Diamond*>::iterator it = diamonds.begin(); it != diamonds.end(); it++)
{
std::list<Point2D> listOfTheStaticPoints =(*it)->getThePointsCountingForTheIntersections();

if( !listOfTheStaticPoints.empty() )
{
bool ja = false;
for (std::list<Point2D>::iterator it2 = listOfTheStaticPoints.begin(); it2 != listOfTheStaticPoints.end(); it2++)
{

float dx = superBallSPositionX - (*it2).x;
float dy = superBallSPositionY - (*it2).y; //Ca c'est du Master! Ca, c'est un Dim'Mac!

float distance = sqrt( (float)(dx*dx + dy*dy) );
if(distance <= superBallSRadius)
{
ja=true;
}

}
if(ja) listeResultante.push_back(*it);
}

}

for (std::list<Mine*>::iterator it = mines.begin(); it != mines.end(); it++)
{
std::list<Point2D> listOfTheStaticPoints =(*it)->getThePointsCountingForTheIntersections();

if( !listOfTheStaticPoints.empty() )
{
bool ja = false;
for (std::list<Point2D>::iterator it2 = listOfTheStaticPoints.begin(); it2 != listOfTheStaticPoints.end(); it2++)
{

float dx = superBallSPositionX - (*it2).x;
float dy = superBallSPositionY - (*it2).y;

float distance = sqrt( (float)(dx*dx + dy*dy) );
if(distance <= superBallSRadius)
{
ja=true;
}

}
if(ja) listeResultante.push_back(*it);
}

}
return listeResultante;
}


void spawnNewSpaceObjects(int a)
{
gamesContents->addOneRandomDiamond();
if(rand()%2==1) gamesContents->addOneMine(superBallSPositionX, superBallSPositionY, superBallSRadiusMax*3.0f);
glutPostRedisplay();
if(!gameOver) glutTimerFunc(milliSecondsIntervalForSpawningNewSpaceObjects, spawnNewSpaceObjects, 0); //we register again this same function to the timer, as it seems to be called only once
}

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

y2k.tm_hour = 0; y2k.tm_min = 0; y2k.tm_sec = 0;
y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

time(&timer); /* get current time; same as: timer = time(NULL) */

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

void displayTheScore()
{
/*
char *c;
glRasterPos3f(screenWidth-100, 40,0);
for (c = gamesContents->playersScoreAsString; *c != '\0'; c++)
{
glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
}
*/

char *c;
glPushMatrix();
glTranslatef(screenWidth-120, 40,0);
glScalef(0.19f,-0.19f,0);
glColor3fv( colorOfTheScore );
for (c=gamesContents->playersScoreAsString; *c != '\0'; c++)
{
glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
}
glPopMatrix();

}

void displayGameOver()
{
char* string1 = "Game Over"; 
char *c;
glPushMatrix();
glTranslatef(screenWidth/2.0f - 356, screenHeight/2.0f + 50,0);
glScalef(1.0f,-1.0f,0);
GLfloat color[3] = {0.0f, 0.5f, 0.05f};
glColor3fv( color );
for (c=string1; *c != '\0'; c++)
{
glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
}
glPopMatrix();

//draw the button

glBegin(GL_POLYGON);
        glVertex2f(ButtonX, ButtonY);
        glVertex2f(ButtonX, ButtonY+ButtonHEIGHT);
        glVertex2f(ButtonX+ButtonWIDTH, ButtonY+ButtonHEIGHT);
        glVertex2f(ButtonX+ButtonWIDTH, ButtonY);
    glEnd();

//play again writing
char* string = "Play Again";
glPushMatrix();
glTranslatef(100, 100, 0);
glScalef(0.2f, -0.2f, 0);
GLfloat color2[3] = {0.0f, 0.0f, 1.0f};
glColor3fv( color2 );

for (c=string; *c != '\0'; c++)
{
glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
}
glPopMatrix();
}


void drawTheBall(int x, int y, float r)
{
glColor3fv( superBallsColor );

    glBegin(GL_TRIANGLES);

    for (float i = 0.0f; i < PI2; i+=one_fifteenth_PI)
    {
glVertex3f(x, y, 0);
glVertex3f(x + r * cos(i), y + r * sin(i),0);
glVertex3f(x + r * cos(i+one_fifteenth_PI), y + r * sin(i+one_fifteenth_PI),0);
    }

    glEnd();
}

void moveTheBombs(int a)
{

for (std::list<Mine*>::iterator it = gamesContents->mines.begin(); it != gamesContents->mines.end(); it++)
{
float x = (*it)->posX();
float y = (*it)->posY();

Vector2D direction = Vector2D(superBallSPositionX - x, superBallSPositionY - y);
direction *= bombsAttractionFactor/Magnitude(direction);

(*it)->updateTheRandMovementVector();

direction += (*it)->randMovementVector *bombsFactorForThierIndependentRandomMovement / Mine::normOfTheRandMovementVector ;

(*it)->setNewPositionAndUpdateTheIntersectionPoints(x+direction.x, y+direction.y, direction);




//check whether we are in the screen:

if((*it)->posX() > screenWidth)
{
(*it)->setTheComponentXofTheRandomVectorNegative();

direction=Vector2D( screenWidth - (*it)->posX(), 0.0f);
(*it)->setNewPositionAndUpdateTheIntersectionPoints(screenWidth, (*it)->posY(), direction);
}
if((*it)->posX() < 0.0f)
{
(*it)->setTheComponentXofTheRandomVectorPositive();

direction=Vector2D( 0.0f - (*it)->posX(), 0.0f);
(*it)->setNewPositionAndUpdateTheIntersectionPoints(0.0f, (*it)->posY(), direction);
}
if((*it)->posY() > screenHeight)
{
(*it)->setTheComponentYofTheRandomVectorNegative();

direction=Vector2D(0.0f, screenHeight - (*it)->posY());
(*it)->setNewPositionAndUpdateTheIntersectionPoints((*it)->posX(), screenHeight, direction);
}
if((*it)->posY() < 0.0f)
{
(*it)->setTheComponentYofTheRandomVectorPositive();

direction=Vector2D(0.0f, 0.0f - (*it)->posY());
(*it)->setNewPositionAndUpdateTheIntersectionPoints((*it)->posX(), 0.0f, direction);
}


}

//glutTimerFunc(milliSecondsIntervalForMovingTheBombs, moveTheBombs, 0);
}

void updatePositionsOfObjects()
{
superBallSSpeedX += superBallSAX;
superBallSSpeedY += superBallSAY;
superBallSPositionX += superBallSSpeedX;
superBallSPositionY -= superBallSSpeedY;
if(superBallSPositionX+superBallSRadius>screenWidth)
{
superBallSPositionX=screenWidth-superBallSRadius;
if(superBallSAX>0) superBallSAX=0.0f;
if(superBallSSpeedX>0) superBallSSpeedX=0.0f;
}
else if(superBallSPositionX-superBallSRadius<0)
{
superBallSPositionX=superBallSRadius;
if(superBallSAX<0) superBallSAX=0.0f;
if(superBallSSpeedX<0) superBallSSpeedX=0.0f;
}
if(superBallSPositionY+superBallSRadius>screenHeight)
{
superBallSPositionY=screenHeight-superBallSRadius;
if(superBallSAY<0) superBallSAY=0.0f;
if(superBallSSpeedY<0) superBallSSpeedY=0.0f;
}
else if(superBallSPositionY-superBallSRadius<0)
{
superBallSPositionY=superBallSRadius;
if(superBallSAY>0) superBallSAY=0.0f;
if(superBallSSpeedY>0) superBallSSpeedY=0.0f;
}

moveTheBombs(0);
}

void collisionsCheckRightNow_gimmeThisGimmeThat()
{
std::list<SpaceObject*> l1 = SuperBall::getTheObjectsThatTheSuperBallIntersectsNow( gamesContents->diamonds, gamesContents->mines);

if( l1.empty() ) return;

if( gamesContents->checkForMines(l1) )
{

//there is a mine...
gameOver=true;
}
else
{
gamesContents->destroyTheObjectsAndAddThemToTheScore(l1);

itoa((int)(gamesContents->playersScore), gamesContents->playersScoreAsString , 10);
}
}

void display(void)
{
if(!gameOver)
{
updatePositionsOfObjects();
collisionsCheckRightNow_gimmeThisGimmeThat();
}
    glClearColor (openglClearColor[0],openglClearColor[1],openglClearColor[2],openglClearColor[3]);
    glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity();







if(!gameOver) drawTheBall(superBallSPositionX, superBallSPositionY, superBallSRadius);

// binds the texture to any geometry about to be rendered
glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_bomb);

/*
glBegin(GL_QUADS);

glTexCoord2f (0.0, 0.0);
glVertex3f (0.0, 0.0, 0.0);
glTexCoord2f (1.0, 0.0);
glVertex3f (100.0, 0.0, 0.0);
glTexCoord2f (1.0, 1.0);
glVertex3f (100.0, 100.0, 0.0);
glTexCoord2f (0.0, 1.0);
glVertex3f (0.0, 100.0, 0.0);
glEnd();
*/




for (std::list<Mine*>::iterator it = gamesContents->mines.begin(); it != gamesContents->mines.end(); it++)
{
(*it)->drawIt();
}

glDisable(GL_TEXTURE_2D);




for (std::list<Diamond*>::iterator it = gamesContents->diamonds.begin(); it != gamesContents->diamonds.end(); it++)
{
(*it)->drawIt();
}

displayTheScore();

if(gameOver) displayGameOver();

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



void specialKeys(int key, int x, int y)
{
   switch (key) {
case GLUT_KEY_F11: // F11: Toggle between full-screen and windowed mode
fullScreenMode = !fullScreenMode;
if (fullScreenMode)
{
windowPosX = glutGet(GLUT_WINDOW_X);
windowPosY = glutGet(GLUT_WINDOW_Y);
windowWidth = glutGet(GLUT_WINDOW_WIDTH);
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
case 27: //Escape key
phidgetManag->close();
exit(0);
break;
case GLUT_KEY_LEFT:
//Left directional key.
superBallSPositionX-=10;
break;
case GLUT_KEY_UP:
//Up directional key.
superBallSPositionY-=10;
break;
case GLUT_KEY_RIGHT:
//Right directional key.
superBallSPositionX+=10;
break;
case GLUT_KEY_DOWN:
//Down directional key.
superBallSPositionY+=10;
break;






   }
   glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
case 27: //Escape key
fullScreenMode = false;
glutReshapeWindow(windowWidth,windowHeight);
glutPositionWindow(windowPosX,windowPosY);
break;
case 'a':
superBallSPositionX-=10;
break;
case 'w':
superBallSPositionY-=10;
break;
case 'd':
superBallSPositionX+=10;
break;
case 's':
superBallSPositionY+=10;
break;

//37(left arrow); 38(up arrow); 39(right arrow); 40(down arrow)

  }
  glutPostRedisplay();
}

static GLuint
nearestPower( GLuint value )
{
    int i = 1;

    if (value == 0) return -1; /* Error! */
    for (;;) {
         if (value == 1) return i;
         else if (value == 3) return i*4;
         value >>= 1; i *= 2;
    }
}

void startgame()
{

try
{
gamesContents = new GamesContents(screenWidth, screenHeight, 20, 10, superBallSPositionX, superBallSPositionY, 3.0f*superBallSRadiusMax);
}
catch( int i)
{
printf("Exception %d ",i);
char chaaar;
printf("\npress a key and enter. screenWidth = %d, screenHeight= %d ", screenWidth,screenHeight);
scanf("%c",&chaaar);
exit(0);
}

}

/* called when a mouse button is pressed or released */
void MouseButton(int button,int state,int x,int y)
{
if(gameOver && y<ButtonHEIGHT+ButtonY && y>ButtonY && x<ButtonWIDTH+ButtonX && x>ButtonX && state == GLUT_UP)
{
printf("play again clicked \n");
startgame();
gameOver = false;
glutTimerFunc(milliSecondsIntervalForSpawningNewSpaceObjects, spawnNewSpaceObjects, 0);

}


}



/* called when the mouse moves */
void MouseMove(int x,int y)
{
/* Pass information about the position of the mouse to pui */

}




int main(int argc, char **argv)
{


superBallSPositionX = 300;
superBallSPositionY= 400;
superBallSRadius = 80;
superBallSSpeedX = 0.0f;
superBallSSpeedY = 0.0f;

glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize( glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT) );
    glutInitWindowPosition(400,150);
char* s = "Super Ball";
glutCreateWindow(s);
screenWidth = glutGet(GLUT_WINDOW_WIDTH);//glutGet(GLUT_SCREEN_WIDTH);
screenHeight = glutGet(GLUT_WINDOW_HEIGHT);//glutGet(GLUT_SCREEN_HEIGHT);

phidgetManag = new PhidgetManager();
phidgetManag->start();





 startgame();







//load the textures:

//texture_bomb = LoadTexture("bomb.bmp");

texture_bomb = TextureLoad("bomb.bmp",
            GL_FALSE, /* I - Generate alpha for bitmap */
            GL_LINEAR_MIPMAP_LINEAR, /* I - Minification filter */
            GL_LINEAR, /* I - Magnification filter */
            GL_REPEAT);

/*
glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

int imageWidth = 300;
int imageHeight = 278;
GLsizei sWidth, sHeight;
sWidth = nearestPower( imageWidth );
sHeight = nearestPower( imageHeight );
imageData = (GLubyte *)malloc( sHeight*sWidth*4*sizeof( GLubyte ) );
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData); //the texture width and height must be a power of two
glEnable( GL_TEXTURE_2D );
*/







glutFullScreen();

glutTimerFunc(milliSecondsIntervalForSpawningNewSpaceObjects, spawnNewSpaceObjects, 0);


    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMove);
    glutIdleFunc(spindisplay);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);
    glutMainLoop();

}

	HRESULT NuiGetSensorCount(
         int *pCount)
