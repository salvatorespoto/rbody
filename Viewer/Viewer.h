// Viewer.h
#pragma once

#include <GLFW\glfw3.h>
#include <glad/glad.h>

#include "Shader.h"



/**
 * Callback used from GLFW to report errors
 *
 * @param error The reported error code
 * @param description A description of the error
 */
void glfwErrorCallback(int error, const char* description);


class Viewer 
{

private:

	GLFWwindow* windowHandle;	
	int windowWidth = 800;		
	int windowHeight = 600;	
	int viewportWidth;		
	int viewportHeight;		

	Shader* vertexShader;			
	Shader* pixelShader;
	GLuint shaderProgram;


public:

	/**
	 * Callback Called on framebuffer resize event
	 *
	 * @param window An handle to the current window
	 * @param width	The new framebuffer width
	 * @param height The new framebuffer height
	 */
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

	/**
	 * Return the singleton instance of the Viewer
	 */
	static Viewer& GetInstance();

	/**
	 * Run the application
	 */
	void Run();

	/**
	 * Init window using the GLFW library
	 */
	void InitGLFW();

	/**
	 * Init OpenGL
	 */
	void InitOpenGL();
};