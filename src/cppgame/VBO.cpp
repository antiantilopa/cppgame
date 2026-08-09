#include "include/VBO.h"
#include <glad/glad.h>

VBO::VBO(std::vector<Vertex3d> vertices, unsigned char mode, unsigned int reserve){
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    if (mode == Vertex3d::NOTHING) return;
    unsigned int usage = GL_STATIC_DRAW;
    if (reserve > 1){
        usage = GL_DYNAMIC_DRAW;
    }
    unsigned int reserve_ = vertices.size() * sizeof(Vertex3d);
    if (reserve_ < reserve)
        reserve_ = reserve;
    glBufferData(GL_ARRAY_BUFFER, reserve_, vertices.data(), usage);
}

VBO::VBO(std::vector<Vertex2d> vertices, unsigned char mode, unsigned int reserve){
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    if (mode == Vertex2d::NOTHING) return;
    unsigned int usage = GL_STATIC_DRAW;
    if (reserve > 1){
        usage = GL_DYNAMIC_DRAW;
    }
    unsigned int reserve_ = vertices.size() * sizeof(Vertex2d);
    if (reserve_ < reserve)
        reserve_ = reserve;
    glBufferData(GL_ARRAY_BUFFER, reserve_, vertices.data(), usage);
}

void VBO::rewrite(std::vector<Vertex2d> verticies){
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, verticies.size() * sizeof(Vertex2d), verticies.data());
}

void VBO::rewrite(std::vector<Vertex3d> verticies){
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, verticies.size() * sizeof(Vertex3d), verticies.data());
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
