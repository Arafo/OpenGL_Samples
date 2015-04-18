#include <windows.h>
#include <iostream>
#define GLFW_INCLUDE_GL_3
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "board.h"
#include "world.h"

void ogl_init(GLFWwindow* win);
void ogl_reshape(GLFWwindow* win,int width,int height);
void ogl_display(GLFWwindow* win);

void keyboard(GLFWwindow* win,int key,int s,int act,int mod);
void mouse(GLFWwindow* win,int but,int act,int mod);
void motion(GLFWwindow* win,double x,double y);

using namespace std;

int main(int argc,char* argv[])
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API,GLFW_OPENGL_API);
#if 1
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_FALSE);
#else
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
#endif

	GLFWwindow* win;

	win = glfwCreateWindow(512,512,"OGL Application",NULL,NULL);
	if (!win)
		return 0;

	ogl_init(win);

	glfwSetFramebufferSizeCallback(win,ogl_reshape);
	glfwSetWindowRefreshCallback(win,ogl_display);

	glfwSetKeyCallback(win,keyboard);
	glfwSetMouseButtonCallback(win,mouse);

	while (!glfwWindowShouldClose(win))
	{
		glfwWaitEvents();
	}

	return 0;
}

void ogl_init(GLFWwindow* win)
{
	glfwMakeContextCurrent(win);

	cout << "GL Version: " << glGetString(GL_VERSION) << endl;
	cout << "SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
	cout << flush;

	world_init();
	board_init();
}

void ogl_reshape(GLFWwindow* win,int width,int height)
{
	cout << "reshape" << endl;
	glfwMakeContextCurrent(win);
	world_reshape(width,height);
}

void ogl_display(GLFWwindow* win)
{
	cout << "display" << endl;
	glfwMakeContextCurrent(win);
	world_display();
	board_display();

	glfwSwapBuffers(win);
}

void keyboard(GLFWwindow* win,int key,int s,int act,int mod)
{
	if (act!=GLFW_PRESS)
		return;

	cout << "key " << char(key) << endl;

	switch (key)
	{
		case GLFW_KEY_Q:
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(win,GL_TRUE);
			break;
		default:
			break;
	}

	ogl_display(win);
//	glutPostRedisplay();
}

void mouse(GLFWwindow* win,int but,int act,int mod)
{
	cout << "mouse" << endl;
	switch(act)
	{
		case GLFW_PRESS:
			glfwSetCursorPosCallback(win,motion);
			break;
		case GLFW_RELEASE:
			glfwSetCursorPosCallback(win,0);
			break;
	}

	ogl_display(win);
//	glutPostRedisplay();
}

void motion(GLFWwindow* win,double x,double y)
{
	cout << "motion " << x << " " << y << endl;

	ogl_display(win);
//	glutPostRedisplay();
}
