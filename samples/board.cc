#ifdef WIN32
#include <windows.h>
#endif

#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
//#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "board.h"

void cuadro();

void board_init() 
{
	glClearColor(0.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW_MATRIX);
	glClear(GL_COLOR_BUFFER_BIT);
	//gluOrtho2D(0.0, 120.0, 0.0, 140.0);
}

void board_reshape(int w, int h)
{

}

void board_display()
{
    // angle of rotation for the camera direction
    float x = 0, z = 0, lx = 0, lz = 0;
    // Clear Color and Depth Buffers
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	x, 1.0f, z,
              x+lx, 1.0f,  z+lz,
              0.0f, 1.0f,  0.0f);
    
    // Draw ground
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f,  100.0f);
    glVertex3f( 100.0f, 0.0f,  100.0f);
    glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();
    
    // Draw 36 SnowMen
	for(int i = -3; i < 3; i++) {
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*1.0,0,j * 2.0);
			//drawSnowMan();
			glPopMatrix();
		}
    }
    
    
	for (int i = 0; i < 8; i++)
	{
		glPushMatrix();
		// Trasladar a la fila
        glTranslated(0, i + 1, 0);
		for (int j = 0; j < 8; j++)
		{
			glPushMatrix();
			// Trasladar a la columna
            glTranslated(j + 1, 0, 0);
			if ((i + j) % 2)
				// Color verde
				glColor3d(0.0, 1.0, 0.0);
			else
				// Color rojo
				glColor3d(1.0, 0.0, 0.0);
			cuadro();
			glPopMatrix();
		}
		glPopMatrix();
	}

}

void board_clean() 
{


}

void cuadro() 
{
    glBegin(GL_QUADS);
    glColor3f(0.05f,0.05f,0.05f);
    glVertex3f(0.0f,0.0f,-1.5f);
    glVertex3f(1.50f,0.0f,-1.5f);
    glVertex3f(1.5f,0.3f,-1.5f);
    glVertex3f(0.0f,0.3f,-1.5f);
    glEnd();
}