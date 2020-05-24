#include "stdafx.h"
#include "Shader.h"


Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	//Store the given file path
	vertexPath = vertexShaderPath;
	fragmentPath = fragmentShaderPath;
	setup();
}

Shader::~Shader()
{
}

void Shader::setup()
{
	//If the path is valid, load the shader
	if (vertexPath != "" && fragmentPath != "") {
		loadShader();
	}
}

GLint Shader::getShaderID()
{
	return shaderID;
}

GLint Shader::getModelMatrixLoc()
{
	return modelMatrixLocation;
}

GLint Shader::getViewMatrixLoc()
{
	return viewMatrixLocation;
}

GLint Shader::getProjectionMatrixLoc()
{
	return projectionMatrixLocation;
}

void Shader::loadShader()
{
	/*** Read in the shaders ***/
	std::ifstream fileStream;
	//Open the file at the directory for reading input
	fileStream.open(vertexPath, std::ios::in);

	//Make sure the filestream is functional
	if (!fileStream.is_open() || !fileStream.good()) {
		std::cout << "Could not open file from directory: " << vertexPath << std::endl;
	}
	vertexShader = "";
	std::string readLine;
	
	//Read in each line, add a newline at the end of each
	while (std::getline(fileStream, readLine)) {
		vertexShader += readLine + "\n";
	}
	
	//Close the istream
	fileStream.close();

	//Open the file at the directory for reading input
	fileStream.open(fragmentPath, std::ios::in);
	
	//Make sure the filestream is functional
	if (!fileStream.is_open() || !fileStream.good()) {
		std::cout << "Could not open file from directory: " << fragmentPath << std::endl;
	}
	fragmentShader = "";
	readLine = "";
	
	//Read in each line, add a newline at the end of each
	while (std::getline(fileStream, readLine)) {
		fragmentShader += readLine + "\n";
	}
	
	//Close the istream
	fileStream.close();

	const char* vertShader = vertexShader.c_str();
	const char* fragShader = fragmentShader.c_str();

	/*** Compile the shader program ***/

	//Load and compile the vertex and fragment shaders
	GLuint vertShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShaderID, 1, &vertShader, NULL);
	glCompileShader(vertShaderID);

	GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShaderID, 1, &fragShader, NULL);
	glCompileShader(fragShaderID);

	//Compile the complete shader program
	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertShaderID);
	glAttachShader(shaderID, fragShaderID);

	//Link the new shader program
	glLinkProgram(shaderID);

	modelMatrixLocation = glGetUniformLocation(shaderID, "model_matrix");
	viewMatrixLocation = glGetUniformLocation(shaderID, "view_matrix");
	projectionMatrixLocation = glGetUniformLocation(shaderID, "projection_matrix");

	//Check for linking errors
	GLint linked;
	glGetProgramiv(shaderID, GL_LINK_STATUS, &linked);
	if (!linked) {
		GLsizei len;
		glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(shaderID, len, &len, log);
		std::cerr << "Shader linking failed: " << log << std::endl;
		delete[] log;
	}
}