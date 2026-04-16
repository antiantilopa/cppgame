#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>
#include <vector>
#include "vertex.h"

class VBO
{
public:
	unsigned int ID; // id of VBO object in GPU
	VBO(std::vector<Vertex3d> verticies, unsigned char mode = Vertex3d::POS);
	VBO(std::vector<Vertex2d> verticies, unsigned char mode = Vertex2d::POS);

	void bind();
	void unbind();
	void Delete();
};

#endif