#pragma once
#include <GL\GL.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLprimatives
{
public:
	GLprimatives();
	~GLprimatives();

	void drawLine(float x1, float y1, float x2, float y2);
	void drawRectangle(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	void drawCircle(float cx, float cy, float r, int num_segments);
	void drawFilledCircle(float x1, float y1, float x2, float y2, float angle, double radius, float color1, float color2, float color3);

	const float DEG2RAD = 3.14159 / 180;
};