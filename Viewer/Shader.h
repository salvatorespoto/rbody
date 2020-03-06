// Shader.h
#pragma once

#include <string>



/** 
 * This class load from a text file and compile a vertex or fragment shader 
 */
class Shader
{

public:

	/** 
	 * Shader id 
	 */
	GLuint Id = 0;

	/**
	 * Compile a the shader 
	 *
	 * @param path the shader full path
	 * @param type GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
	 */
	Shader(const std::string& path, GLenum type);
};

