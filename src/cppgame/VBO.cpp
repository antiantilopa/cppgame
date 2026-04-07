#include "include/VBO.h"
#include <glad/glad.h>

VBO::VBO(float* vertices, unsigned long long int size){
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::bind(){
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void VBO::unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VBO::Delete(){
    glDeleteBuffers(1, &ID);
}
