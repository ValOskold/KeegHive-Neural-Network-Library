#pragma once
#include <glm\glm\mat4x4.hpp>
#include <glm\glm\gtx\transform.hpp>
#include "Shader.h"

class Sprite
{
public:
	Sprite(const GLfloat * verts, const GLfloat * vertColors, const GLint vertCount, const Shader * shader, GLenum drawMode = GL_TRIANGLES);
	~Sprite();

	//How the vertices should be drawn
	GLenum drawMode;

	//Bind buffer arrays and shader matrix uniform locations
	void setup();

	//Calculate and return the final model matrix
	glm::mat4 getModelMatrix();

	//Function returns the number of vertices
	GLint getVertCount() const;

	//Get reference to the shader
	Shader* getShader() const;

	//Functions to get the transformation matrices
	glm::mat4 getTranslationMatrix();
	glm::mat4 getRotationMatrix();
	glm::mat4 getScaleMatrix();

	//Functions for relative transformations
	void rotateAround(glm::vec3 axis, float degrees);
	void translate(glm::vec3 move);
	void scale(glm::vec3 relativeAmount);

	//Functions for identity-based transformations
	void setRotation(glm::vec3 axis, float degrees);
	void setPosition(glm::vec3 location);
	void setScale(glm::vec3 scale);

	//Function returns vertex array ID
	GLuint getVertexArrayID();

private:
	//Vertex buffer objects
	GLuint VBOID[2];	//List of buffer objects
	GLuint VAOID;	//Buffer object array ref

	//Vertex count
	GLint vertexCount;

	//Vertex information
	GLfloat* vertices;
	GLfloat* vertexColors;

	//Shader files and information
	Shader* shader;

	//Individual matrices for rotation, position, and scale
	glm::mat4 rotationMatrix;
	glm::mat4 translationMatrix;
	glm::mat4 scaleMatrix;

	//Final matrix representing the model in space
	glm::mat4 modelMatrix;
};