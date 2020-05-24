#include "stdafx.h"
#include "Renderer.h"


Renderer::Renderer(GLFWwindow* window)
{
	setWindowRef(window);
}


Renderer::~Renderer()
{
}

void Renderer::setWindowRef(GLFWwindow * window)
{
	this->window = window;
}

void Renderer::renderSprite(Sprite * sprite)
{
	//Bind the model's vertex array id
	glBindVertexArray(sprite->getVertexArrayID());
	//Link the shader program ID
	glLinkProgram(sprite->getShader()->getShaderID());
	//Use the shader program!
	glUseProgram(sprite->getShader()->getShaderID());
	//Apply the model position matrix
	glUniformMatrix4fv(sprite->getShader()->getModelMatrixLoc(), 1, GL_FALSE, &sprite->getModelMatrix()[0][0]);
	//Apply the view matrix
	glUniformMatrix4fv(sprite->getShader()->getViewMatrixLoc(), 1, GL_FALSE, &cameraView[0][0]);
	//Apply the perspective matrix
	glUniformMatrix4fv(sprite->getShader()->getProjectionMatrixLoc(), 1, GL_FALSE, &projMatrix[0][0]);
	//Draw the model's points from the currently bound VAO with currently used shader
	glDrawArrays(sprite->drawMode, 0, sprite->getVertCount());
}

void Renderer::renderSpriteAtPos(Sprite * sprite, int pos)
{
	//Bind the model's vertex array id
	glBindVertexArray(sprite->getVertexArrayID());
	//Link the shader program ID
	glLinkProgram(sprite->getShader()->getShaderID());
	//Use the shader program!
	glUseProgram(sprite->getShader()->getShaderID());
	//Apply the model position matrix
	glUniformMatrix4fv(sprite->getShader()->getModelMatrixLoc(), 1, GL_FALSE, &sprite->getModelMatrix()[0][0]);
	//Apply the view matrix
	glUniformMatrix4fv(sprite->getShader()->getViewMatrixLoc(), 1, GL_FALSE, &viewMatrixes.at(pos)[0][0]);
	//Apply the perspective matrix
	glUniformMatrix4fv(sprite->getShader()->getProjectionMatrixLoc(), 1, GL_FALSE, &projectionMatrixes.at(pos)[0][0]);
	//Draw the model's points from the currently bound VAO with currently used shader
	glDrawArrays(sprite->drawMode, 0, sprite->getVertCount());
}

void Renderer::renderSpriteAtCam(Sprite * sprite, rCamera* cam)
{
	//Bind the model's vertex array id
	glBindVertexArray(sprite->getVertexArrayID());
	//Link the shader program ID
	glLinkProgram(sprite->getShader()->getShaderID());
	//Use the shader program!
	glUseProgram(sprite->getShader()->getShaderID());
	//Apply the model position matrix
	glUniformMatrix4fv(sprite->getShader()->getModelMatrixLoc(), 1, GL_FALSE, &sprite->getModelMatrix()[0][0]);
	//Apply the view matrix
	glUniformMatrix4fv(sprite->getShader()->getViewMatrixLoc(), 1, GL_FALSE, &cam->cameraView[0][0]);
	//Apply the perspective matrix
	glUniformMatrix4fv(sprite->getShader()->getProjectionMatrixLoc(), 1, GL_FALSE, &cam->projMatrix[0][0]);
	//Draw the model's points from the currently bound VAO with currently used shader
	glDrawArrays(sprite->drawMode, 0, sprite->getVertCount());
}

void Renderer::setViewMatrix(glm::vec3 cameraLocation, glm::vec3 cameraTarget, glm::vec3 cameraUp)
{
	camLoc = cameraLocation;
	camTar = cameraTarget;
	camUp = cameraUp;
	cameraView = glm::lookAt(camLoc, camTar, camUp);
}

void Renderer::setProjectionMatrix(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nearPlane, GLfloat farPlane)
{
	projMatrix = glm::frustum(left, right, bottom, top, nearPlane, farPlane);
}

void Renderer::setViewMatrixAtPos(glm::vec3 cameraLocation, glm::vec3 cameraTarget, glm::vec3 cameraUp, int pos)
{
	cameraLocations.at(pos) = cameraLocation;
	cameraTargets.at(pos) = cameraTarget;
	cameraUpDirs.at(pos) = cameraUp;
	viewMatrixes.at(pos) = glm::lookAt(camLoc, camTar, camUp);
}

void Renderer::setProjectionMatrixAtPos(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nearPlane, GLfloat farPlane, int pos)
{
	projectionMatrixes.at(pos) = glm::frustum(left, right, bottom, top, nearPlane, farPlane);
}

void Renderer::initDefaultView()
{
	setViewMatrix(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	setProjectionMatrix(-0.5f, 0.5f, -0.5f, 0.5f, 0.2f, 10.0f);
}

void Renderer::initDefaultViewAtPos(int pos)
{
	setViewMatrixAtPos(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),pos);
	setProjectionMatrixAtPos(-0.5f, 0.5f, -0.5f, 0.5f, 0.2f, 10.0f, pos);
}

void Renderer::loadNewCamera(std::string n)
{
	rCamera* cam = new rCamera();
	cameraList.push_back(cam);
	cam->camName = n;
}

struct::Renderer::rCamera* Renderer::getCameraAtPos(int pos)
{
	return cameraList.at(pos);
}

void Renderer::rCamera::setViewMatrix(glm::vec3 cameraLocation, glm::vec3 cameraTarget, glm::vec3 cameraUp)
{
	camLoc = cameraLocation;
	camTar = cameraTarget;
	camUp = cameraUp;
	cameraView = glm::lookAt(camLoc, camTar, camUp);
}

void Renderer::rCamera::setProjectionMatrix(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nearPlane, GLfloat farPlane)
{
	projMatrix = glm::frustum(left, right, bottom, top, nearPlane, farPlane);
}