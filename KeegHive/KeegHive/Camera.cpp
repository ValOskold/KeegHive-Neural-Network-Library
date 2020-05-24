#include "stdafx.h"
#include "Camera.h"
#include <glm\glm\gtx/vector_angle.hpp>

Camera::Camera()
{
	projectionMatrix = glm::mat4(1);
	minRenderDistance = 0.05f;
	maxRenderDistance = 256.0f;
	lastWindowWidth = 1.0f;
	lastWindowHeight = 1.0f;
	FOV = 60.0f;
	//calculateProjectionMatrix(100.0f, 100.0f);
}

Camera::Camera(float _windowWidth, float _windowHeight, float _fieldOfView, float _farPlane, float _nearPlane)
{
	minRenderDistance = _nearPlane;
	maxRenderDistance = _farPlane;
	lastWindowHeight = _windowHeight;
	lastWindowWidth = _windowWidth;
	FOV = _fieldOfView;

	//calculateProjectionMatrix(lastWindowWidth, lastWindowHeight);
}

Camera::~Camera()
{
}

float Camera::getFOV()
{
	return FOV;
}

void Camera::setFOV(float _fieldOfView)
{
	FOV = _fieldOfView;
	//calculateProjectionMatrix(lastWindowWidth, lastWindowHeight);
}

glm::mat4 Camera::getProjectionMatrix()
{
	return projectionMatrix;
}

glm::mat4 Camera::getViewMatrix()
{
	return viewMatrix;
}
/*
void Camera::setViewMatrix(glm::vec3 cameraLocation, glm::vec3 cameraTarget, glm::vec3 cameraUp)
{
	camLoc = cameraLocation;
	camTar = cameraTarget;
	camUp = cameraUp;
	viewMatrix = glm::lookAt(camLoc, camTar, camUp);
}

void Camera::setProjectionMatrix(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nearPlane, GLfloat farPlane)
{
	projectionMatrix = glm::frustum(left, right, bottom, top, nearPlane, farPlane);
}

void Camera::calculateProjectionMatrix(float _windowWidth, float _windowHeight)
{
	float ratio = _windowWidth / _windowHeight;
	top = tan(FOV * glm::pi<float>() / 360.0f) * minRenderDistance;
	bottom = -top;
	left = ratio * bottom;
	right = ratio * top;
	projectionMatrix = glm::frustum(left, right, bottom, top, minRenderDistance, maxRenderDistance);
}

void Camera::initDefaultView()
{
	setViewMatrix(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	setProjectionMatrix(-0.5f, 0.5f, -0.5f, 0.5f, 0.2f, 10.0f);
}
*/