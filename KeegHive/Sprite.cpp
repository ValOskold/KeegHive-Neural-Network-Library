#include "stdafx.h"
#include "Sprite.h"

Sprite::Sprite(const GLfloat * verts, const GLfloat * vertColors, const GLint vertCount, const Shader * shader, GLenum drawMode)
{
	float vertSize = vertCount * 3 * sizeof(GLfloat);
	this->vertexCount = vertCount;

	this->drawMode = drawMode;

	//Allocate memory for the verex information (3 floats for position, 3 floats for color)
	vertices = (GLfloat*)malloc(vertSize);
	vertexColors = (GLfloat*)malloc(vertSize);

	//Copy over the vertex information
	vertices = (GLfloat*)memcpy(vertices, verts, vertSize);
	vertexColors = (GLfloat*)memcpy(vertexColors, vertColors, vertSize);

	//Copy the shader data
	this->shader = new Shader(*shader);

	setup();
}

Sprite::~Sprite()
{
}

void Sprite::setup()
{
	//Generate the points VBO, bind it and copy the points onto the buffer
	VBOID[0] = 0;
	glGenBuffers(1, &VBOID[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOID[0]);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	//Generate the colors VBO, bind it and copy the points onto the buffer
	VBOID[1] = 0;
	glGenBuffers(1, &VBOID[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOID[1]);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(GLfloat), vertexColors, GL_STATIC_DRAW);

	//Create the vertex array object to hold our VBOs and bind it
	glGenVertexArrays(1, &VAOID);
	glBindVertexArray(VAOID);
	//Bind our first (point) buffer to the VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBOID[0]);
	//Bind the vPosition shader attribute to the 0th VBO (points)
	glBindAttribLocation(shader->getShaderID(), 0, "vPos");
	//Attirbute pointer to the 0th index, 3 of type, type is float, not normalized, 0 stride, no pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//Bind our second (color) buffer to the VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBOID[1]);
	//Bind the vColor shader attribute to the 1st VBO (color)
	glBindAttribLocation(shader->getShaderID(), 1, "vCol");
	//Attirbute pointer to the 1st index, 3 of type, type is float, not normalized, 0 stride, no pointer
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//Enable the vertex attribute arrays
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	modelMatrix = glm::mat4(1.0);
	translationMatrix = glm::mat4(1.0);
	rotationMatrix = glm::mat4(1.0);
	scaleMatrix = glm::mat4(1.0);
}

glm::mat4 Sprite::getModelMatrix()
{
	modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	return modelMatrix;
}

GLint Sprite::getVertCount() const
{
	return vertexCount;
}

Shader * Sprite::getShader() const
{
	return shader;
}

glm::mat4 Sprite::getTranslationMatrix()
{
	return translationMatrix;
}

glm::mat4 Sprite::getRotationMatrix()
{
	return rotationMatrix;
}

glm::mat4 Sprite::getScaleMatrix()
{
	return scaleMatrix;
}

void Sprite::rotateAround(glm::vec3 axis, float degrees)
{
	rotationMatrix *= glm::rotate(glm::radians(degrees), axis);
}

void Sprite::translate(glm::vec3 move)
{
	translationMatrix = glm::translate(translationMatrix, move);
}

void Sprite::scale(glm::vec3 relativeAmount)
{
	scaleMatrix = glm::scale(scaleMatrix, relativeAmount);
}

void Sprite::setRotation(glm::vec3 axis, float degrees)
{
	rotationMatrix = glm::rotate(glm::radians(degrees), axis);
}

void Sprite::setPosition(glm::vec3 location)
{
	translationMatrix = glm::translate(glm::mat4(1.0), location);
}

void Sprite::setScale(glm::vec3 scale)
{
	scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
}

GLuint Sprite::getVertexArrayID()
{
	return VAOID;
}