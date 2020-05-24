#version 400
layout(location = 0) in vec4 vPos;
layout(location = 1) in vec4 vCol;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

out vec4 fCol;

void main(){
	fCol = vCol;
	gl_Position = projection_matrix * view_matrix * model_matrix * vPos;
}