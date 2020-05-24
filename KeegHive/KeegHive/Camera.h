#pragma once
#include <glm\glm\vec3.hpp>
#include <glm\glm\mat4x4.hpp>
#include <glm\glm\gtc/matrix_transform.hpp>
#include <glm\glm\gtc/quaternion.hpp>
class Camera
{
public:
	Camera();
	Camera(float _windowWidth, float _windowHeight, float _fieldOfView = 60.0f, float _farPlane = 256.0f, float _nearPlane = 0.05f);
	~Camera();

	float getFOV();
	void setFOV(float _fieldOfView);

	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();
	//void setViewMatrix(glm::vec3 cameraLocation, glm::vec3 cameraTarget, glm::vec3 cameraUp);
	//void setProjectionMatrix(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nearPlane, GLfloat farPlane);

	inline float getNearPlane()
	{
		return minRenderDistance;
	}

	inline float getFarPlane()
	{
		return maxRenderDistance;
	}

	float top, bottom, left, right;

private:
	glm::vec3 camLoc, camTar, camUp;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

	float FOV;

	float maxRenderDistance;
	float minRenderDistance;

	float lastWindowWidth;
	float lastWindowHeight;

	//void calculateProjectionMatrix(float _windowWidth, float _windowHeight);
	//void initDefaultView();
};