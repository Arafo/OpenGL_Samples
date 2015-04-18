#include <windows.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "world.h"

using namespace std;

static float vtx[][2] = {
	{-0.5f, -0.5f},
	{ 0.5f, -0.5f},
	{ 0.5f,  0.5f},
	{-0.5f,  0.5f}
};
static float clr[][3] = {
	{1.0f, 0.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 0.0f, 1.0f},
	{1.0f, 1.0f, 1.0f}
};

GLUquadricObj *quadric;

void world_init()
{
	glClearColor(0,0,0,0);
	quadric = gluNewQuadric();
}

void world_reshape(int w,int h)
{
//	cout << w << " x " << h << endl;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
}

void world_display()
{
//	cout << "dis" << endl;
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
	glColor3f(0.9, 0.3, 0.2);
	glScalef(2.0, 1.0, 1.0);
	gluSphere(quadric, 5, 20, 20);
}

void world_clean()
{
}
