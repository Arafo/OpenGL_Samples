#ifdef WIN32
#include <windows.h>
#endif

#include <iostream>
#include <time.h>

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
void peon(int i, int j);

void board_init() 
{
	glClearColor(0, 0, 0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-2, 2, -1.5, 1.5, 1, 40);
    
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //glTranslatef(0, 0, -3);
    //glRotatef(50, 1, 0, 0);
    //glRotatef(70, 0, 1, 0);
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
    for (GLfloat i = -3; i <= 3*8; i += 0.3) {
        glVertex3f(i, 0, 3.0f); glVertex3f(i, 0, -3.0f);
        glVertex3f(3.0f, 0, i); glVertex3f(-3.0f, 0, i);
    }
    glEnd();
    
    //int max_peones = 8;
    //int peones = 0;
    // Semilla
    //srand (time(NULL));
    
    // Tablero de ajedrez 8x8
	for (int i = 0; i < 8; i++)
	{
		glPushMatrix();
		// Trasladar a la fila
        glTranslatef(0.0f, 0.0f, i*3.0f);
		for (int j = 0; j < 8; j++)
		{
			glPushMatrix();
			// Trasladar a la columna
            glTranslatef(j*3.0f, 0.0f, 0.0f);
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
    peon(0, 0);
    peon(2, 2);
    peon(0, 1);
}

void board_clean() 
{
    
}

void cuadro() 
{
    glBegin(GL_QUADS);
    glVertex3f(0.0f,0.0f,0.0f); // Vertice inferior izquierdo
    glVertex3f(3.0f,0.0f,0.0f); // Vertice inferior derecho
    glVertex3f(3.0f,0.0f,-3.0f); // Vertice superior derecho
    glVertex3f(0.0f,0.0f,-3.0f); // Vertice superior izquierdo
    glEnd();
}

void peon(int x, int y) 
{    
    GLUquadric *quadric = gluNewQuadric();
    glColor3f(0.0f, 0.0f, 1.0f);
    
	glPushMatrix();
    glTranslated(x*3.0f + 1.5f, 0.0f, y*3.0f - 1.5f);
    glRotated(-90.0f, 1, 0, 0);
    
    // Base
    gluCylinder(quadric, 1.25f, 1.25f, 0.4f, 20, 20);
    
    // Disco inferior
    glTranslated(0.0f, 0.0f, 0.4f);
    gluDisk(quadric, 0, 1.1f, 20, 1);
    
    // Cono
    glTranslatef(0.0f ,0.0f, 0.4f);
    gluCylinder(quadric, 1.0f, 0.3f, 1.0f, 20, 20);
    
    // Cilindro central
    glTranslatef(0.0f, 0.0f, 1.0f);
    gluCylinder(quadric, 0.3f, 0.3f, 1.5f, 20, 20);
    
    // Cabeza
    glRotated(90.0f, 1, 0, 0);
    glTranslatef(0.0f, 1.5f, 0.0f);
    gluSphere(quadric, 0.6f, 20, 20);
    
    // Disco superior
    glRotated(-90.0f, 1, 0, 0);
    glTranslatef(0.0f, 0.0f, -0.6f);
    gluDisk(quadric, 0, 0.6f, 20, 20);
    
	glPopMatrix();
}