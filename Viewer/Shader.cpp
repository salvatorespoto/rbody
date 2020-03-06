// Shader.cpp

#define GLFW_INCLUDE_NONE

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Shader.h"


Shader::Shader(const std::string& path, GLenum type)
{
	// Set exceptions condition mask
	std::ifstream inFile;
	inFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	// Open the shader file source and read the shader code 
	std::string code;
	try
	{
		inFile.open(path);
		std::stringstream stream;
		stream << inFile.rdbuf();
		inFile.close();
		code = stream.str();
	}
	catch (std::ifstream::failure e)
	{
		throw std::runtime_error("Cannot read shader source file " + path);
	}

	// Compile shader
	Id = glCreateShader(type);
	const char* shaderCode = code.c_str();
	glShaderSource(Id, 1, &shaderCode, NULL);
	glCompileShader(Id);

	// Check for compilation success
	int success;
	char infoLog[1024];
	glGetShaderiv(Id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(Id, 1024, NULL, infoLog);
		throw std::runtime_error("Error compiling shader " + std::string(path) + ":" + infoLog);
	}
}
