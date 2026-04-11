#ifndef MESH_H
#define MESH_H

#include "VBO.h"
#include "VAO.h"
#include "EBO.h"



class Mesh{
public:
    VAO* vao;
    VBO* vbo;
    EBO* ebo;
    Mesh();
};

#endif