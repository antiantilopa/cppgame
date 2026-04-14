#ifndef SHADER_H
#define SHADER_H

#include <filesystem>
#include <string>
#include "glm/glm.hpp"

class Shader{
public:
    unsigned int ID;
    bool compiled_correctly;
    Shader(const char* vertex_shader_file, const char* fragment_shader_file);
    Shader(const std::filesystem::path& vertex_shader_file, const std::filesystem::path& fragment_shader_file);
    Shader(const std::string& vertex_shader_file, const std::string& fragment_shader_file);
    ~Shader();

    void activate();
    template<typename T>
    void setUniform(const char* name, T* value_ptr, int dim = 1);
    template<typename T>
    void setUniform(const char* name, T value);
    void setUniformMatrix(const char* name, glm::mat4 value);
    void setUniformMatrix(const char* name, glm::mat3 value);
    void setUniformMatrix(const char* name, glm::mat2 value);
};


#endif