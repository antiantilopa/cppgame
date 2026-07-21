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

    static std::vector<Vertex3d> EMPTY_VERTICES_VECTOR;
    static std::vector<unsigned int> EMPTY_INDICES_VECTOR;
    static std::vector<Texture> EMPTY_TEXTURE_VECTOR;
    Mesh(std::vector<Vertex3d>& vertices = EMPTY_VERTICES_VECTOR, unsigned char mode = Vertex3d::NOTHING, std::vector<unsigned int>& indices = EMPTY_INDICES_VECTOR, std::vector<Texture>& textures = EMPTY_TEXTURE_VECTOR);
    void draw(
        Shader& shader, 
        Camera* camera = nullptr, 
        glm::mat4 matrix = glm::mat4(1.0f),
        glm::vec3 trans = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::quat rot = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
    );
};

#endif