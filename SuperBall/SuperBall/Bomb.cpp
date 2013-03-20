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

		//texture
		GLuint bombTexture;
		glGenTextures(1, &bombTexture);
		glBindTexture(GL_TEXTURE_2D, bombTexture);
		
		// select modulate to mix texture with color for shading
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

		// when texture area is small, bilinear filter the closest mipmap
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                 GL_LINEAR_MIPMAP_NEAREST );
		// when texture area is large, bilinear filter the original
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		// the texture wraps over at the edges (repeat)
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

		BYTE * data;
		FILE * file;
		int imgwidth = 256, imgheight = 256; //to change with an actual image

		// allocate buffer
		data = malloc( width * height * 3 );
		// open and read texture data
		file = fopen( filename, "rb" );
		fread( data, width * height * 3, 1, file );
		fclose( file );

		glEnd();

	}
	
};



