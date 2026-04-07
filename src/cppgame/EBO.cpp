#include "include/EBO.h"
#include <glad/glad.h>

EBO::EBO(unsigned int* indices, unsigned long long int size){
    glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::bind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
void EBO::unbind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void EBO::Delete(){
    glDeleteBuffers(1, &ID);
}
