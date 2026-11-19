#pragma once

#include <glad/glad.h>

class RBO{
public:
	unsigned int ID;

	RBO();

	// storing color in render buffer is outdated or is used for optimization on mobile.
	// here, this format is not available. please refrain from using it.
	void setStorage(int width, int height, int format = GL_DEPTH24_STENCIL8);
	void bind();
	void unbind();
	void Delete();
};



