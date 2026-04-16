#include "include/VBO.h"
#include <glad/glad.h>

VBO::VBO(std::vector<Vertex3d> vertices, unsigned char mode){
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex3d), vertices.data(), GL_STATIC_DRAW);
}

VBO::VBO(std::vector<Vertex2d> vertices, unsigned char mode){
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex2d), vertices.data(), GL_STATIC_DRAW);
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
