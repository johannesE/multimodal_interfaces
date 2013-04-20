#include "Mine.h"
#include <math.h>
#include "glut.h"
/*#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
*/

#define PI2 6.283185307f
#define one_tenth_PI 0.31141592654f
//GLuint bombtexture;



Mine::Mine(float x, float y) : SpaceObject(x,y,0) 
{ 
	buildThePointsCountingForTheIntersection();
	randMovementVector = Vector2D(rand(), rand());
	randMovementVector *= normOfTheRandMovementVector/Magnitude(randMovementVector);
	//glEnable( GL_TEXTURE_2D );
	//bombtexture = LoadTextureRAW( "texture.raw", TRUE );
}

Mine::Mine(float x, float y, double scoreForThePlayer) : SpaceObject(x,y,scoreForThePlayer) 
{ 
	buildThePointsCountingForTheIntersection(); 
	randMovementVector = Vector2D(rand(), rand());
	randMovementVector *= normOfTheRandMovementVector/Magnitude(randMovementVector);
	//glEnable( GL_TEXTURE_2D );
	//bombtexture = LoadTextureRAW( "bomb.raw", TRUE );
}


Mine::~Mine(void)
{
//	FreeTexture( bombtexture );
}

// load a 256x256 RGB .RAW file as a texture
/*GLuint LoadTextureRAW( const char * filename, int wrap )
{
    GLuint texture;
    int width, height;
    BYTE * data;
    FILE * file;

    // open texture data
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;

    // allocate buffer
    width = 300;
    height = 278;
	data = malloc( width * height * 3 );

    // read texture data
    fread( data, width * height * 3, 1, file );
    fclose( file );

    // allocate a texture name
    glGenTextures( 1, &texture );

    // select our current texture
    glBindTexture( GL_TEXTURE_2D, texture );

    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                     GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the first mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                     wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                     wrap ? GL_REPEAT : GL_CLAMP );

    // build our texture mipmaps
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,
                       GL_RGB, GL_UNSIGNED_BYTE, data );

    // free buffer
    /free( data );

    return texture;
}*/


void Mine::drawIt()  //called from the main loop
{
	//glEnable( GL_TEXTURE_2D );
    //glBindTexture( GL_TEXTURE_2D, bombtexture );


	glBegin(GL_TRIANGLES);

		GLfloat color[3] = {0.0, 0.0, 0.0};
		glColor3fv(color);

		for(float a=0; a<PI2; a+=one_tenth_PI)
		{
			glVertex3f(x, y ,0);
			glVertex3f(x + cos(a)*radius, y-sin(a)*radius ,0);
			glVertex3f(x + cos(a+one_tenth_PI)*radius, y-sin(a+one_tenth_PI)*radius ,0);
		}
    glEnd();
}

void Mine::buildThePointsCountingForTheIntersection()
{

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