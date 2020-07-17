#include "stdafx.h"
#include "WindowManager.h"
#include <Windows.h>
//#define GLFW_EXPOSE_NATIVE_X11
//#define GLFW_EXPOSE_NATIVE_GLX
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <iomanip>
#include <string>
#include <SOIL\SOIL.h>
#include "Controller.h"
WindowManager::WindowManager()
{
}


WindowManager::~WindowManager()
{
}

int WindowManager::width = 0;
int WindowManager::height = 0;
GLFWwindow* WindowManager::window;
HWND hwnd;

GLFWwindowrefreshfun windowUpdateCallback()
{
	GLFWwindow* w = WindowManager::window;
	int width, height;
	glfwGetWindowSize(w, &width, &height);
	glViewport(0, 0, width, height);

	glfwSwapBuffers(w);
	//glfwPollEvents();
	//glfwWaitEvents();

	//resized = false;
	return GLFWwindowrefreshfun();
}

void WindowManager::create()
{
	std::string title = "Game";//Polyvox | Ver " + std::string(1.3) + " | FPS : " + std::to_string(Display::frameRate);
	glfwDefaultWindowHints();
	//glfwWindowHint(GLFW_DECORATED, 0);
	width = 2000;
	height = 1300;
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	glfwSetWindowSizeCallback(window, &displayResizeCallback);
	glfwSetWindowPos(window, 1400, 50);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	glfwShowWindow(window);
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool toggling = false;
bool fullscreen = false;

int windowedX = 0, windowedY = 0;
int windowedWidth = 0, windowedHeight = 0;

void WindowManager::update()
{
	if (Controller::isKeyDown(GLFW_KEY_F11))
	{
		if (!toggling)
		{
			if (!fullscreen)
			{
				const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
				glfwWindowHint(GLFW_RED_BITS, mode->redBits);
				glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
				glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
				glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

				glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
				fullscreen = true;
			}
			else if (fullscreen)
			{
				glfwSetWindowMonitor(window, nullptr, windowedX, windowedY, windowedWidth, windowedHeight, 0);
				//window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
				//glfwSetWindowSizeCallback(window, &displayResizeCallback);
				//glfwSetWindowPos(window, 1400, 50);
				//glfwSetWindowSize(window, width, height);
				fullscreen = false;
			}

			toggling = true;
		}
	}
	else
	{
		toggling = false;
	}
	if (!fullscreen)
	{
		windowedX = 0;
		windowedY = 0;
		windowedWidth = width;
		windowedHeight = height;
		glfwGetWindowPos(window, &windowedX, &windowedY);
	}
	glfwGetWindowSize(window, &width, &height);
	glViewport(0, 0, width, height);
	
	glfwSwapBuffers(window);
	glfwPollEvents();
	//glfwWaitEvents();
	
	resized = false;

}
bool WindowManager::resized = true;
void WindowManager::displayResizeCallback(GLFWwindow* _window, int _width, int _height)
{
	resized = true;
}

int WindowManager::getWidth()
{
	return width;
}

int WindowManager::getHeight()
{
	return height;
}

bool WindowManager::wasResized()
{
	return resized;
}

void WindowManager::setTextCallback(GLFWcharfun f)
{
	glfwSetCharCallback(window, f);
}

void WindowManager::setKeyCallback(GLFWkeyfun f)
{
	glfwSetKeyCallback(window, f);
}

int WindowManager::closeRequested()
{
	return glfwWindowShouldClose(window);
}

void WindowManager::showMouse()
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void WindowManager::hideMouse()
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void WindowManager::centerCursor()
{
	glfwSetCursorPos(window, width / 2, height / 2);
}


