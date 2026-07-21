#ifndef MODEL_H
#define MODEL_h

#include "vbo.h"
#include "ebo.h"
#include "fileopener.h"
#include "texture.h"
#include "mesh.h"
#include <filesystem>
#include <string>
#include <json/json.hpp>

using json = nlohmann::json;

class Model{
public:
    Model(const char* path);
    Model(std::filesystem::path& path);
    Model(std::string& path);
    void draw(
    Shader& shader, 
    Camera& camera, 
    glm::vec3 trans = glm::vec3(0.0f, 0.0f, 0.0f), 
    glm::quat rot = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
private:

    std::vector<Mesh> meshes;
    std::vector<glm::vec3> translations;
    std::vector<glm::quat> rotations;
    std::vector<glm::vec3> scales;
    std::vector<glm::mat4> matrices;

    const char* file;
    std::vector<unsigned char> data;
    json JSON;

    std::vector<std::string> loaded_tex_names;
    std::vector<Texture> loaded_textures;
    
    void loadMesh(unsigned int mesh_ind);
    void traverseNode(unsigned int next_node_ind, glm::mat4 prev_matrix = glm::mat4(1.0f));

    std::vector<unsigned char> getData();
    std::vector<float> getFloats(json accessor);
    std::vector<unsigned int> getIndices(json accessor);

    std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floats);
    std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floats);
    std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floats);

    std::vector<Vertex3d> assembleVertices(
        std::vector<glm::vec3> positions,
        std::vector<glm::vec3> normals,
        std::vector<glm::vec2> tex_coords
    );

    std::vector<Texture> getTextures();
};

#endif 