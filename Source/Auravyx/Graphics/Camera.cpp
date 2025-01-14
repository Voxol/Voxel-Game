#include "Auravyx/Graphics/Camera.h"
#include "Auravyx/UI/Control/Controller.h"
#include "Auravyx/Core/Clock.h"
#include "Auravyx/Utility/Math/M.h"
#include "Auravyx/Core/Chat.h"
#include "Auravyx/Utility/Profiler.h"
#include "Auravyx/UI/Window.h"
#include <Logger/Log.h>
#include <cmath>
bool f3Lock = false;
bool f5Lock = false;

double PI = 3.14159265;
void Camera::getPlayerInput()
{
	xVel = 0;
	yVel = 0;
	zVel = 0;
	if (!Chat::isChatting)
	{
		if (!f3Lock && Window::getWindow()->getController()->isKeyDown(GLFW_KEY_F3))
		{
			f3Lock = true;
			Profiler::showAdvancedDebugInfo = !Profiler::showAdvancedDebugInfo;
		}
		else if (!Window::getWindow()->getController()->isKeyDown(GLFW_KEY_F3))
		{
			f3Lock = false;
		}
		if (!f5Lock && Window::getWindow()->getController()->isKeyDown(GLFW_KEY_F5))
		{
			f5Lock = true;
			Profiler::showChunkMetrics = !Profiler::showChunkMetrics;
		}
		else if (!Window::getWindow()->getController()->isKeyDown(GLFW_KEY_F5))
		{
			f5Lock = false;
		}
		if (Window::getWindow()->getController()->isKeyDown(GLFW_KEY_E))
		{
			speed *= 10;
		}
		if (Window::getWindow()->getController()->isAction(Action::MOVE_FORWARDS))
		{
			xVel -= sin(M::toRadians(yRot)) * (speed);
			zVel -= cos(M::toRadians(yRot)) * (speed);
		}
		if (Window::getWindow()->getController()->isAction(Action::MOVE_BACKWARDS))
		{
			xVel += sin(M::toRadians(yRot)) * (speed);
			zVel += cos(M::toRadians(yRot)) * (speed);
		}
		if (Window::getWindow()->getController()->isAction(Action::MOVE_LEFT))
		{
			xVel -= cos(M::toRadians(yRot)) * (speed);
			zVel += sin(M::toRadians(yRot)) * (speed);
		}
		if (Window::getWindow()->getController()->isAction(Action::MOVE_RIGHT))
		{
			xVel += cos(M::toRadians(yRot)) * (speed);
			zVel -= sin(M::toRadians(yRot)) * (speed);
		}
		if (Window::getWindow()->getController()->isKeyDown(GLFW_KEY_SPACE))
		{
			yVel += (speed);
		}
		if (Window::getWindow()->getController()->isKeyDown(GLFW_KEY_LEFT_SHIFT))
		{
			yVel -= (speed);
		}
		xVel *= speedMultiplier;
		yVel *= speedMultiplier;
		zVel *= speedMultiplier;
		xRot += (double)Window::getWindow()->getController()->getMouseDY() * (double) 0.3;
		yRot += (double)Window::getWindow()->getController()->getMouseDX() * (double) 0.3;
	}

	xPos += Clock::get(xVel);
	yPos += Clock::get(yVel);
	zPos += Clock::get(zVel);

	if (yPos < 32.5)
	{
		//yPos = 32.5;
	}
	if (xRot > 90)
	{
		xRot = 90;
	}
	else if (xRot < -90)
	{
		xRot = -90;
	}
	yRot = fmod(yRot, 360);

	x = xPos +sin(yRot * (PI / 180)) * 1.5 * (sin(((xRot + 90) * (PI / 180))));
	y = yPos - sin(xRot * (PI / 180)) * 1.5 + 1.7;
	z = zPos +cos(yRot * (PI / 180)) * 1.5 * (sin(((xRot + 90) * (PI / 180))));

	cX = floor((xPos * 1) / Chunk::CHUNK_SIZE);
	cY = floor((yPos * 1) / Chunk::CHUNK_SIZE);
	cZ = floor((zPos * 1) / Chunk::CHUNK_SIZE);

	//Log::out(std::to_string((xRot) / 90) + " " + std::to_string(yRot) + " " + std::to_string((sin(((xRot + 90) * (3.145 / 180))))));
	speed = 4;
}
void Camera::set(double x, double y, double z, double xRot, double yRot, double zRot)
{
	this->x = x;
	this->y = y;
	this->z = z;

	this->xRot = xRot;
	this->yRot = yRot;
	this->zRot = zRot;
}

double Camera::getXRot()
{
	return xRot;
}

double Camera::getYRot()
{
	return yRot;
}

double Camera::getZRot()
{
	return zRot;
}

double Camera::getX()
{
	return x;
}

double Camera::getY()
{
	return y;
}

double Camera::getZ()
{
	return z;
}

Matrix4f Camera::getViewMatrix() const
{
	Matrix4f matrix;
	matrix.createViewMatrix(x, y, z, xRot, yRot, zRot);
	return matrix;
}

void Camera::setSpeedMultiplier(double x)
{
	this->speedMultiplier = x;
}

void Camera::setFOV(double fov)
{
	this->fov = fov;
}
