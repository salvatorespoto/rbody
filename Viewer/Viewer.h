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

/** 
 * Implements the Viewer application 
 */
class Viewer 
{
public:

	/**
	 * Return the singleton instance of the Viewer
	 */
	static Viewer& GetInstance();

	void Run();

	/**
	 * Callback Called on framebuffer resize event
	 *
	 * @param window An handle to the current window
	 * @param width	The new framebuffer width
	 * @param height The new framebuffer height
	 */
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

private:

	GLFWwindow* windowHandle = NULL;	
	int windowWidth = 800;		
	int windowHeight = 600;	
	int viewportWidth = 800;		
	int viewportHeight = 600;		

	Shader* vertexShader = NULL;			
	Shader* pixelShader = NULL;
	GLuint shaderProgram = 0;

	void InitGLFW();
	void InitOpenGL();
	void RenderLoop();	
	void HandleKeyboardInput();
};