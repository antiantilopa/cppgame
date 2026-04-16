#ifndef VAO_H
#define VAO_H

#include "VBO.h"
#include <glad/glad.h>

class VAO
{
public:
	unsigned int ID;

	VAO();
	~VAO();

	void LinkVBO(VBO& VBO, unsigned char mode, char dim); // links verticies with given mode. dim either 2 or 3
	void LinkVBO(VBO& VBO, unsigned int layout, int size = 3, int type = GL_FLOAT, unsigned int stride = 0, void* offset = 0);// Links a VBO to the VAO using a certain layout
	void bind();
	void unbind();
	void Delete();
};



#endif