#ifndef MODEL_H
#define MODEL_h

#include "vbo.h"
#include "ebo.h"
#include <filesystem>
#include <string>

class Model{
public:
    VBO& vbo;
    EBO& ebo;

    Model(float* verices, unsigned int* indicies);
    Model(const char* path);
    Model(std::filesystem::path& path);
    Model(std::string& path);
    ~Model();
    void bind();
    void unbind();
    void Delete();
};

#endif 