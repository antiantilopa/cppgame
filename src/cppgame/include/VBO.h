#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

class VBO
{
public:
	unsigned int ID; // id of VBO object in GPU
	VBO(float* vertices, unsigned long long int size);

	void bind();
	void unbind();
	void Delete();
};

#endif