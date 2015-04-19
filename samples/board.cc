#ifdef WIN32
#include <windows.h>
#endif

#include <iostream>

#ifdef __APPLE__
//#include <GLUT/glut.h>
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
	glClearColor(0.5, 0.5, 1.0, 0.0);
}

void board_reshape(int w, int h)
{
    glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);

}

void board_display(float x, float y, float z)
{
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(2.0f, 1.0f, 0.0f,
              x, y,  z,
              0.0f, 1.0f,  0.0f);
    
    std::cout << "x:" << x << std::endl;
    std::cout << "y:" << y << std::endl;
    std::cout << "z:" << z << std::endl;
    
    // Suelo
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f,  100.0f);
    glVertex3f( 100.0f, 0.0f,  100.0f);
    glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();
    
	for (int i = 0; i < 8; i++)
	{
		glPushMatrix();
		// Trasladar a la fila
        glTranslatef(0.0f, 0.0f, -i*0.5f);
		for (int j = 0; j < 8; j++)
		{
			glPushMatrix();
			// Trasladar a la columna
            glTranslatef(j*0.5f, 0.0f, 0.0f);
			if ((i + j) % 2)
				// Color verde
				glColor3f(0.0, 1.0, 0.0);
			else
				// Color rojo
				glColor3f(1.0, 0.0, 0.0);
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
    glVertex3f(0.0f,0.0f,0.0f); // Vertice inferior izquierdo
    glVertex3f(0.5f,0.0f,0.0f); // Vertice inferior derecho
    glVertex3f(0.5f,0.5f,0.0f); // Vertice superior derecho
    glVertex3f(0.0f,0.5f,0.0f); // Vertice superior izquierdo
    glEnd();
}