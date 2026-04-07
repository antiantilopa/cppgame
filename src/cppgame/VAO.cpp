#include "include/VAO.h"
#include <glad/glad.h>

VAO::VAO(){
	glGenVertexArrays(1, &ID);
}

void VAO::LinkVBO(VBO& VBO, unsigned int layout, int size, int type, unsigned int stride, void* offset){
	VBO.bind();
	glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.unbind();
}

void VAO::bind(){
	glBindVertexArray(ID);
}
void VAO::unbind(){
	glBindVertexArray(0);
}
void VAO::Delete(){
	glDeleteVertexArrays(1, &ID);
}