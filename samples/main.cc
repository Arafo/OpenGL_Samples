#ifdef WIN32
#include <windows.h>
#include <GL/glew.h>
#endif

#include <iostream>
//#include <GL/glew.h>
#define GLFW_INCLUDE_GL_3
#include <GLFW/glfw3.h>
#include <math.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "board.h"
#include "world.h"

void ogl_init(GLFWwindow* win);
void ogl_reshape(GLFWwindow* win,int width,int height);
void ogl_display(GLFWwindow* win);

void keyboard(GLFWwindow* win,int key,int s,int act,int mod);
void mouse(GLFWwindow* win,int but,int act,int mod);
void motion(GLFWwindow* win,double x,double y);

using namespace std;

float z=2.0f, x=12.0f,y=4.0f;
int doHSR = 1;

int main(int argc,char* argv[])
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API,GLFW_OPENGL_API);
#if 1
    #ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,2);
    #else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    #endif
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_FALSE);
#else
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
#endif

	GLFWwindow* win;

	win = glfwCreateWindow(800 ,600,"OGL Application",NULL,NULL);
	if (!win)
		return 1;

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

	//world_init();
	board_init();
}

void ogl_reshape(GLFWwindow* win,int width,int height)
{
	cout << "reshape" << endl;
	glfwMakeContextCurrent(win);
    board_reshape(width, height);
	//world_reshape(width,height);
}

void ogl_display(GLFWwindow* win)
{
	cout << "display" << endl;
	glfwMakeContextCurrent(win);
	//world_display();
	board_display(x, y, z, doHSR);

	glfwSwapBuffers(win);
}

void keyboard(GLFWwindow* win,int key,int s,int act,int mod)
{
	if (act!=GLFW_PRESS)
		return;

	cout << "key " << char(key) << endl;
    
    float fraction = 1.0f;

	switch (key)
	{
		case GLFW_KEY_Q:
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(win,GL_TRUE);
			break;
        case GLFW_KEY_LEFT:
            x = x - fraction;
            break;
        case GLFW_KEY_RIGHT:
            x = x + fraction;
            break;
        case GLFW_KEY_UP:
            z = z + fraction;
            break;
        case GLFW_KEY_DOWN:
            z = z - fraction;
            break;
        case GLFW_KEY_SPACE:
            y = y + fraction;
            break;
        case GLFW_KEY_RIGHT_ALT:
            y = y - fraction;
            break;
        case GLFW_KEY_ENTER:
            if (doHSR == 0) doHSR = 1;
            else doHSR = 0;
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
