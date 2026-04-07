#ifndef EBO_CLASS_H
#define EBO_CLASS_H

class EBO
{
public:
	unsigned int ID;
    
	EBO(unsigned int* indices, unsigned long long int size);
	void bind();
	void unbind();
	void Delete();
};

#endif