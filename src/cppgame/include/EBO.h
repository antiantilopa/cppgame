#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <vector>

class EBO
{
public:
	unsigned int ID;
    
	EBO(std::vector<unsigned int> indices);
	void bind();
	void unbind();
	void Delete();
};

#endif