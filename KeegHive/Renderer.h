#pragma once
#include "Sprite.h"
//#include "Camera.h"
#include "GLFW\glfw3.h"
#include <vector>

class Renderer
{
	struct rCamera {
		std::string camName;
		glm::vec3 camLoc, camTar, camUp;
		glm::mat4 projMatrix;
		glm::mat4 cameraView;

		void setViewMatrix(glm::vec3 cameraLocation, glm::vec3 cameraTarget, glm::vec3 cameraUp);
		void setProjectionMatrix(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nearPlane, GLfloat farPlane);

	};

public:
	Renderer(GLFWwindow* window);
	~Renderer();

	void setWindowRef(GLFWwindow* window);

	void renderSprite(Sprite* sprite);
	void renderSpriteAtPos(Sprite* sprite, int pos);
	void renderSpriteAtCam(Sprite* sprite, rCamera* cam);

	void setViewMatrix(glm::vec3 cameraLocation, glm::vec3 cameraTarget, glm::vec3 cameraUp);
	void setProjectionMatrix(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nearPlane, GLfloat farPlane);

	void setViewMatrixAtPos(glm::vec3 cameraLocation, glm::vec3 cameraTarget, glm::vec3 cameraUp, int pos);
	void setProjectionMatrixAtPos(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nearPlane, GLfloat farPlane, int pos);

	void loadNewCamera(std::string n);
	rCamera* getCameraAtPos(int pos);

private:
	void initDefaultView();
	void initDefaultViewAtPos(int pos);

	GLFWwindow* window;
	glm::vec3 camLoc, camTar, camUp;
	glm::mat4 projMatrix;
	glm::mat4 cameraView;

	int cameraTotal;
	std::vector < glm::vec3> cameraLocations;
	std::vector < glm::vec3> cameraTargets;
	std::vector < glm::vec3> cameraUpDirs;
	std::vector < glm::mat4 > projectionMatrixes;
	std::vector < glm::mat4> viewMatrixes;

	std::vector<rCamera*> cameraList;
};