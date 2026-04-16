#ifndef MESH_H
#define MESH_H

#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "texture.h"
#include "vertex.h"
#include "shader.h"
#include "camera.h"

#include "glm/glm.hpp"

class Mesh{
public:
    VAO* vao;
    VBO* vbo;
    EBO* ebo;
    std::vector <Texture> textures;
    std::vector <Vertex3d> vertices;
    std::vector <unsigned int> indices;

    static std::vector<Texture> EMPTY_TEXTURE_VECTOR;
    Mesh(std::vector<Vertex3d>& vertices, unsigned char mode, std::vector<unsigned int>& indices, std::vector<Texture>& textures = EMPTY_TEXTURE_VECTOR);
    void draw(Shader& shader, Camera* camera = nullptr);
};

#endif