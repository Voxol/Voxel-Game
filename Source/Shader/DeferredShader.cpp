#include "stdafx.h"
#include "DeferredShader.h"
#include <iostream>
#include "Matrix4f.h"

DeferredShader::DeferredShader()
{
	shader = "Deferred";
}

DeferredShader::~DeferredShader()
{
}

void DeferredShader::loadAllUniformLocations()
{
	sunDirection = getUniformLocation("sunDirection");
	cameraPosition = getUniformLocation("cameraPosition");
	farPlane = getUniformLocation("farPlane");
	//glBindAttribLocation(shaderProgram, 1, "normal");
	normal = getUniformLocation("normal");
	viewMatrix = getUniformLocation("viewMatrix");
	depthMVP = getUniformLocation("depthMVP");
	pointLightCount = getUniformLocation("pointLightCount");
	ambientLight = getUniformLocation("ambientLight");

	loadTexture("albedo", 0);
	loadTexture("normal", 1);
	loadTexture("specular", 2);
	loadTexture("glow", 3);
	loadTexture("position", 4);
	loadTexture("shadowMap", 5);
}

void DeferredShader::loadSunDirection(float x, float y, float z)
{
	loadVec3f(sunDirection, x, y, z);
}

void DeferredShader::loadCamera(float x, float y, float z, float farPlane, Matrix4f viewMatrix)
{
	loadVec3f(cameraPosition, x, y, z);
	loadFloat(this->farPlane, farPlane);
	loadMatrix4f(this->viewMatrix, viewMatrix);
}

void DeferredShader::loadDepthMVP(Matrix4f mat)
{
	loadMatrix4f(this->depthMVP, mat);
}

/*void DeferredShader::loadPointLights(std::vector<PointLight> lights)
{
	int i = 0;
	for (auto p : lights)
	{
		std::string light = "pointLights[" + std::to_string(i) + "].";
		GLuint position = glGetUniformLocation(shaderProgram, std::string(light + "position").c_str());
		GLuint colour = glGetUniformLocation(shaderProgram, std::string(light + "colour").c_str());
		GLuint power = glGetUniformLocation(shaderProgram, std::string(light + "power").c_str());
		GLuint length = glGetUniformLocation(shaderProgram, std::string(light + "length").c_str());
		GLuint falloff = glGetUniformLocation(shaderProgram, std::string(light + "falloff").c_str());

		loadVec3f(position, p.position.x, p.position.y, p.position.z);
		loadVec3f(colour, p.colour.x, p.colour.y, p.colour.z);
		loadFloat(power, p.power);
		loadFloat(length, p.length);
		loadFloat(falloff, p.falloff);
		i++;
	}
	loadFloat(pointLightCount, i);
}*/

void DeferredShader::loadAmbientLight(float light, float r, float g, float b)
{
	loadVec4f(ambientLight, light, r, g, b);
}
