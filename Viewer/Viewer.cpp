// Viewer.cpp

#define GLFW_INCLUDE_NONE
#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Viewer.h"

void glfwErrorCallback(int error, const char* description)
{
	throw std::runtime_error("GLFW error:" + std::string(description));
}

Viewer& Viewer::GetInstance() 
{
    static Viewer instance;
    return instance;
}

void Viewer::Run() 
{
	InitGLFW();
	InitOpenGL();
	RenderLoop();	// Starts the render loop
}

void Viewer::InitGLFW()
{
	glfwInit();
	glfwSetErrorCallback(glfwErrorCallback);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	windowHandle = glfwCreateWindow
	(
		windowWidth,
		windowHeight,
		"Viewer",
		nullptr,
		nullptr
	);

	if (!windowHandle)
	{
		glfwTerminate();
		throw std::runtime_error("Error initializing GLFW window");
	}

	viewportWidth = windowWidth;
	viewportHeight = windowHeight;

	glfwSetFramebufferSizeCallback(windowHandle, FramebufferSizeCallback);
}

void Viewer::InitOpenGL()
{
	glfwMakeContextCurrent(windowHandle);
	glfwGetFramebufferSize(windowHandle, &viewportWidth, &viewportHeight);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("Failed to initialize extension loader library GLAD");
	}

	// Load and compile vertex and fragment shaders
	vertexShader = new Shader("shader.vert", GL_VERTEX_SHADER);
	pixelShader = new Shader("shader.frag", GL_FRAGMENT_SHADER);
	
	// Build the shader program from single shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader->Id);
	glAttachShader(shaderProgram, pixelShader->Id);
	glLinkProgram(shaderProgram);

	int success;
	char infoLog[1024];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		throw std::runtime_error("Error creating shader program" + std::string(infoLog));
	}
}

void Viewer::RenderLoop() 
{
	while (!glfwWindowShouldClose(windowHandle))
	{
		glfwGetFramebufferSize(windowHandle, &viewportWidth, &viewportHeight);


		glfwSwapBuffers(windowHandle);
		glfwPollEvents();
	}
}

void Viewer::HandleKeyboardInput()
{
	// ESC: exit application
	if (glfwGetKey(windowHandle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(windowHandle, true);
}

void Viewer::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}