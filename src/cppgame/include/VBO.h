#pragma once

#include <glad/glad.h>
#include <vector>
#include "vertex.h"

class VBO{
public:
	unsigned int ID; // id of VBO object in GPU
	VBO(std::vector<Vertex3d> verticies, unsigned char mode = Vertex3d::POS, unsigned int reserve = 0);
	VBO(std::vector<Vertex2d> verticies, unsigned char mode = Vertex2d::POS, unsigned int reserve = 0);

	void bind();
	void unbind();
	void rewrite(std::vector<Vertex2d> verticies);
	void rewrite(std::vector<Vertex3d> verticies);
	void Delete();
};

