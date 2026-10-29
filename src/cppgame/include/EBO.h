#pragma once

#include <vector>

class EBO{
public:
	unsigned int ID;
	EBO(std::vector<unsigned int> indices);
	void bind();
	void unbind();
	void Delete();
};

