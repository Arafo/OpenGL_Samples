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
void peon();

void board_init() 
{
	glClearColor(0.5, 0.5, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-2, 2, -1.5, 1.5, 1, 40);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -3);
    glRotatef(50, 1, 0, 0);
    glRotatef(70, 0, 1, 0);
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
	gluLookAt(x, 2.0f, z,
              1.0f, 0.0f, -1.0f,
              0.0f, 1.0f,  0.0f);     
    
    std::cout << "x:" << x << std::endl;
    std::cout << "y:" << y << std::endl;
    std::cout << "z:" << z << std::endl;
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Suelo
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    for (GLfloat i = -2.5; i <= 2.5; i += 0.25) {
        glVertex3f(i, 0, 2.5); glVertex3f(i, 0, -2.5);
        glVertex3f(2.5, 0, i); glVertex3f(-2.5, 0, i);
    }
    glEnd();
    
    // Tablero de ajedrez
	for (int i = 0; i < 8; i++)
	{
		glPushMatrix();
		// Trasladar a la fila
        glTranslatef(0.0f, 0.0f, -i*0.25f);
		for (int j = 0; j < 8; j++)
		{
			glPushMatrix();
			// Trasladar a la columna
            glTranslatef(j*0.25f, 0.0f, 0.0f);
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
    glVertex3f(0.25f,0.0f,0.0f); // Vertice inferior derecho
    glVertex3f(0.25f,0.0f,-0.25f); // Vertice superior derecho
    glVertex3f(0.0f,0.0f,-0.25f); // Vertice superior izquierdo
    glEnd();
}

void peon() 
{
//    GLUquadricObj *quadric;
//    quadric = gluNewQuadric();
//    
//    glColor3f(1.0f, 0.5f , 0.5f);
//
//    glPushMatrix();
//    // Base
//	glTranslatef(0.0f ,0.75f, 0.0f);
//	gluSphere(quadric, 0.75f, 2, 10);
//    
//    // Cuerpo
//	glTranslatef(0.0f, 1.5f, 0.0f);
//	gluCylinder(quadric, 0.2f, 0.2f, 0.4f, 20, 20);
//    
//    // Cabeza
//	glTranslatef(0.0f, 0.4f, 0.0f);
//	gluSphere(quadric, 0.05f, 10, 10);
//    glPopMatrix();
    
    GLUquadric *solid = gluNewQuadric();
    glColor3f(0.0f, 0.0f, 1.0f);
	glPushMatrix();
    glRotated(-90.0f, 1, 0, 0);
    gluDisk(solid, 0, .75, 20, 1);
    gluCylinder(solid, .5, 0, 3, 20, 1);
    glTranslated(0,0,2.6);
    gluSphere(solid, .4, 6, 6);
	glPopMatrix();
    
}