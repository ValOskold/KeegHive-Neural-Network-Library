#include "stdafx.h"
#include "GLprimatives.h"


GLprimatives::GLprimatives()
{
}


GLprimatives::~GLprimatives()
{
}

void GLprimatives::drawLine(float x1, float y1, float x2, float y2)
{
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	float line_vertex[] ={
		x1,y1, x2,y2
	};
	glVertexPointer(2, GL_FLOAT, 0, line_vertex);
	glDrawArrays(GL_LINES, 0, 2);

	glDisable(GL_LINE_SMOOTH);
}

void GLprimatives::drawRectangle(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	float rec_vertex[] = {
		x1, y1,
		x2, y2,
		x3, y3,
		x4, y4
	};
}

void GLprimatives::drawCircle(float cx, float cy, float r, int num_segments)
{
	float theta = 2 * 3.1415926 / float(num_segments);
	float tangetial_factor = tanf(theta);//calculate the tangential factor 

	float radial_factor = cosf(theta);//calculate the radial factor 

	float x = r;//we start at angle = 0 

	float y = 0;

	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++){
		glVertex2f(x + cx, y + cy);//output vertex 

								   //calculate the tangential vector 
								   //remember, the radial vector is (x, y) 
								   //to get the tangential vector we flip those coordinates and negate one of them 

		float tx = -y;
		float ty = x;

		//add the tangential vector 

		x += tx * tangetial_factor;
		y += ty * tangetial_factor;

		//correct using the radial factor 

		x *= radial_factor;
		y *= radial_factor;
	}
	glEnd();
}

void GLprimatives::drawFilledCircle(float x1, float y1, float x2, float y2, float angle, double radius, float color1, float color2, float color3)
{
	glColor3f(color1, color2, color3);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);

	for (angle = 1.0f; angle<361.0f; angle += 0.2){
		x2 = x1 + sin(angle)*radius;
		y2 = y1 + cos(angle)*radius;
		glVertex2f(x2, y2);
	}

	glEnd();
}