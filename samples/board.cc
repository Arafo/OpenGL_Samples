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
    glEnable(GL_COLOR_MATERIAL);
}

void board_reshape(int w, int h)
{
    glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);
    glFrustum(-2, 2, -1.5, 1.5, 1, 40);
	glMatrixMode(GL_MODELVIEW);

}

void board_display(float x, float y, float z, int doHSR)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (doHSR) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
        //gluQuadricDrawStyle(quadric,GLU_FILL);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
        //gluQuadricDrawStyle(quadric,GLU_LINE); 
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        glDisable(GL_COLOR_MATERIAL);
        
    }

    glEnable(GL_LIGHT0);
    glLightf(GL_LIGHT0 ,GL_SPOT_CUTOFF,20); 
    glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,5);
    
    glEnable(GL_NORMALIZE);
    
    glShadeModel(GL_SMOOTH);
    glShadeModel(GL_FLAT);
    
    float m_diff [4] = {0.6 ,0.6 ,0.6 ,1};
    float m_spec [4] = {0.4 ,0.4 ,0.4 ,1}; 
    float m_n = 50;

	glLoadIdentity();
    gluLookAt(x, y, z,
              12.0f, 0.0f, -6.0f,
              0.0f, 1.0f,  0.0f); 
    
    std::cout << "x:" << x << std::endl;
    std::cout << "y:" << y << std::endl;
    std::cout << "z:" << z << std::endl;
    
    //glClear(GL_COLOR_BUFFER_BIT);
    
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
    peon(7, 7);
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
    gluQuadricOrientation(quadric, GLU_OUTSIDE);
    gluQuadricNormals(quadric, GLU_FLAT);
    
    float m_amb [4] = {0.24725, 0.1995, 0.0745 ,1};
    float m_diff [4] = {0.75164, 0.60648, 0.22648,1};
    float m_spec [4] = {0.628281, 0.555802, 0.366065,1}; 
    float m_n = 0.4;
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, m_diff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec); 
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_n * 128.0);
    
    glColor3f(1.0f, 0.843f, 0.0f);
    
	glPushMatrix();
    
    
    glTranslated(x*3.0f + 1.5f, 0.0f, y*3.0f - 1.5f);
    glRotated(-90.0f, 1, 0, 0);
    
    // Base
    gluCylinder(quadric, 1.25f, 1.25f, 0.4f, 100, 100);
    
    // Disco inferior
    glPushMatrix();
    glTranslated(0.0f, 0.0f, 0.4f);
    gluDisk(quadric, 0, 1.25f, 100, 100); // Tapa de la base
    glScalef(1.0f, 1.0f, 0.33f);
    gluSphere(quadric, 1.1f, 100, 100);
    glPopMatrix();
    
    // Cono
    glTranslatef(0.0f ,0.0f, 0.4f);
    gluCylinder(quadric, 1.0f, 0.3f, 1.0f, 100, 100);
    
    // Cilindro central
    glTranslatef(0.0f, 0.0f, 1.0f);
    gluCylinder(quadric, 0.3f, 0.3f, 1.5f, 100, 100);
    
    // Cabeza
    glPushMatrix();
    glRotated(90.0f, 1, 0, 0);
    glTranslatef(0.0f, 1.5f, 0.0f);
    gluSphere(quadric, 0.6f, 100, 100);
    glPopMatrix();
    
    // Disco superior
    glTranslatef(0.0f, 0.0f, 0.9f);
    glScalef(1.0f, 1.0f, 0.24f);
    gluSphere(quadric, 0.6f, 100, 100);

	glPopMatrix();
    
}