#ifdef WIN32
#include <windows.h>
#endif

#include <iostream>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "board.h"

void cuadro();

void board_init() 
{
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0.0, 120.0, 0.0, 140.0);
}

void board_reshape(int w, int h)
{

}

void board_display()
{
	for (int i = 0; i < 8; i++)
	{
		glPushMatrix();
		// Trasladar a la fila
		for (int j = 0; j < 8; j++)
		{
			glPushMatrix();
			// Trasladar a la columna
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
}