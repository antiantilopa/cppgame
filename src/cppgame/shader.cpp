#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cmath>
#include <vector>

#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "include/shader.h"

void Shader::init(const char* vertex_shader_file, const char* geometry_shader_file, const char* fragment_shader_file){
    ID = glCreateProgram();
    this->compiled_correctly = true;
    int local_compiled_correctly;
    int maxLength = 0;
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    if (vertex_shader_file != nullptr){
        std::string vertex_shader_src_str = getFileContents(vertex_shader_file);
        const char* vertex_shader_src = vertex_shader_src_str.c_str();
        glShaderSource(vertex_shader, 1, &vertex_shader_src, NULL);
        glCompileShader(vertex_shader);
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &local_compiled_correctly);
        if (local_compiled_correctly == GL_FALSE){
            this->compiled_correctly = false;
            glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &maxLength);
            char* errorLog = new char[maxLength];
            glGetShaderInfoLog(vertex_shader, maxLength, &maxLength, &errorLog[0]);
            std::cout << "(!) ERROR: vertex shader compilation failed:\n" << &errorLog[0] << std::endl;
            delete[] errorLog;
        }
        glAttachShader(ID, vertex_shader);
    }
    if (geometry_shader_file != nullptr){
        std::string geometry_shader_src_str = getFileContents(geometry_shader_file);
        const char* geometry_shader_src = geometry_shader_src_str.c_str();
        glShaderSource(geometry_shader, 1, &geometry_shader_src, NULL);
        glCompileShader(geometry_shader);

        glGetShaderiv(geometry_shader, GL_COMPILE_STATUS, &local_compiled_correctly);
        if (local_compiled_correctly == GL_FALSE){
            this->compiled_correctly = false;
            glGetShaderiv(geometry_shader, GL_INFO_LOG_LENGTH, &maxLength);
            char* errorLog = new char[maxLength];
            glGetShaderInfoLog(geometry_shader, maxLength, &maxLength, &errorLog[0]);
            std::cout << "(!) ERROR: geometry shader compilation failed:\n" << &errorLog[0] << std::endl;
            delete[] errorLog;
        }
        glAttachShader(ID, geometry_shader);
    }

    if (fragment_shader_file != nullptr){
        std::string fragment_shader_src_str = getFileContents(fragment_shader_file);
        const char* fragment_shader_src = fragment_shader_src_str.c_str();
        glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);
        glCompileShader(fragment_shader);

        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &local_compiled_correctly);
        if (local_compiled_correctly == GL_FALSE){
            this->compiled_correctly = false;
            glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &maxLength);
            char* errorLog = new char[maxLength];
            glGetShaderInfoLog(fragment_shader, maxLength, &maxLength, &errorLog[0]);
            std::cout << "(!) ERROR: fragment shader compilation failed:\n" << &errorLog[0] << std::endl;
            delete[] errorLog;
        }
        glAttachShader(ID, fragment_shader);
    }

    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &local_compiled_correctly);
    if (local_compiled_correctly == GL_FALSE){
        this->compiled_correctly = false;
        glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &maxLength);
        char* errorLog = new char[maxLength];
        glGetProgramInfoLog(ID, maxLength, &maxLength, &errorLog[0]);
        std::cout << "(!) ERROR: shader program linking failed:\n" << &errorLog[0] << std::endl;
        delete[] errorLog;
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(geometry_shader);
    glDeleteShader(fragment_shader);
}
Shader::Shader(const char* vertex_shader_file, const char* geometry_shader_file, const char* fragment_shader_file){
    init(vertex_shader_file, geometry_shader_file, fragment_shader_file);
}
Shader::Shader(
    const std::filesystem::path& vertex_shader_file, 
    const std::filesystem::path& geometry_shader_file, 
    const std::filesystem::path& fragment_shader_file
    ){
    std::string vert_str = vertex_shader_file.string();
    std::string geom_str = geometry_shader_file.string();
    std::string frag_str = fragment_shader_file.string();
    const char* vert_char = vert_str.c_str();
    const char* geom_char = geom_str.c_str();
    const char* frag_char = frag_str.c_str();
    if (vertex_shader_file.empty()){
        vert_char = nullptr;
    }
    if (geometry_shader_file.empty()){
        geom_char = nullptr;
    }
    if (fragment_shader_file.empty()){
        frag_char =nullptr;
    }
    init(vert_char, geom_char, frag_char);
}
Shader::Shader(const std::string& vertex_shader_file, const std::string& fragment_shader_file) : Shader(vertex_shader_file.c_str(), fragment_shader_file.c_str()){}

Shader::~Shader(){
    glDeleteProgram(ID);
}

void Shader::activate(){
    glUseProgram(ID);
}

template<typename T>
void Shader::setUniform(const char* name, T* value_ptr, int dim){
    // Ensure program is active before setting uniforms
    activate();
    int location = glGetUniformLocation(ID, name);
    
    if (location == -1){
        std::cout << "(!) WARNING: uniform '" << name << "' not found in shader program" << std::endl;
        return;
    }
    if constexpr (std::is_same_v<T, float>){
        switch (dim)
        {
        case 1:
            glUniform1f(location, *value_ptr);
            break;
        case 2:
            glUniform2f(location, value_ptr[0], value_ptr[1]);
            break;
        case 3:
            glUniform3f(location, value_ptr[0], value_ptr[1], value_ptr[2]);
            break;
        case 4:
            glUniform4f(location, value_ptr[0], value_ptr[1], value_ptr[2], value_ptr[3]);
            break;
        default:
            std::cout << "(!) WARNING: unsupported uniform dim for type float" << std::endl;
            break;
        }
    } else if constexpr (std::is_same_v<T, int>){
        switch (dim)
        {
        case 1:
            glUniform1i(location, *value_ptr);
            break;
        case 2:
            glUniform2i(location, value_ptr[0], value_ptr[1]);
            break;
        case 3:
            glUniform3i(location, value_ptr[0], value_ptr[1], value_ptr[2]);
            break;
        case 4:
            glUniform4i(location, value_ptr[0], value_ptr[1], value_ptr[2], value_ptr[3]);
            break;
        default:
            std::cout << "(!) WARNING: unsupported uniform dim for type int" << std::endl;
            break;
        }
    } else if constexpr (std::is_same_v<T, unsigned int>){
        switch (dim)
        {
        case 1:
            glUniform1ui(location, *value_ptr);
            break;
        case 2:
            glUniform2ui(location, value_ptr[0], value_ptr[1]);
            break;
        case 3:
            glUniform3ui(location, value_ptr[0], value_ptr[1], value_ptr[2]);
            break;
        case 4:
            glUniform4ui(location, value_ptr[0], value_ptr[1], value_ptr[2], value_ptr[3]);
            break;
        default:
            std::cout << "(!) WARNING: unsupported uniform dim for type unsigned int" << std::endl;
            break;
        }
    } else {
        std::cout << "(!) ERROR: uniform of given type not supported" << std::endl;
    }
}

template void Shader::setUniform<float>(const char* name, float* value_ptr, int dim);
template void Shader::setUniform<int>(const char* name, int* value_ptr, int dim);
template void Shader::setUniform<unsigned int>(const char* name, unsigned int* value_ptr, int dim);

template<typename T>
void Shader::setUniform(const char* name, T value){
    // Ensure program is active before setting uniforms
    activate();
    int location = glGetUniformLocation(ID, name);
    
    if (location == -1){
        std::cout << "(!) WARNING: uniform '" << name << "' not found in shader program" << std::endl;
        return;
    }
    if constexpr (std::is_same_v<T, float>){
        glUniform1f(location, value);
    } else if constexpr (std::is_same_v<T, int>){
        glUniform1i(location, value);
    } else if constexpr (std::is_same_v<T, unsigned int>){
        glUniform1ui(location, value);
    } else if constexpr (std::is_same_v<T, glm::vec2>){
        glUniform2f(location, value.x, value.y);
    } else if constexpr (std::is_same_v<T, glm::vec3>){
        glUniform3f(location, value.x, value.y, value.z);
    } else if constexpr (std::is_same_v<T, glm::vec4>){
        glUniform4f(location, value.x, value.y, value.z, value.w);
    } else {
        std::cout << "(!) ERROR: uniform of given type not supported" << std::endl;
    }
}

template void Shader::setUniform<glm::vec2>(const char* name, glm::vec2 value);
template void Shader::setUniform<glm::vec3>(const char* name, glm::vec3 value);
template void Shader::setUniform<glm::vec4>(const char* name, glm::vec4 value);
template void Shader::setUniform<float>(const char* name, float value);
template void Shader::setUniform<int>(const char* name, int value);
template void Shader::setUniform<unsigned int>(const char* name, unsigned int value);

void Shader::setUniformMatrix(const char* name, glm::mat4 value){
    // Ensure program is active before setting uniforms
    activate();
    int location = glGetUniformLocation(ID, name);
    
    if (location == -1){
        std::cout << "(!) WARNING: uniform '" << name << "' not found in shader program" << std::endl;
        return;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::setUniformMatrix(const char* name, glm::mat3 value){
    // Ensure program is active before setting uniforms
    activate();
    int location = glGetUniformLocation(ID, name);
    
    if (location == -1){
        std::cout << "(!) WARNING: uniform '" << name << "' not found in shader program" << std::endl;
        return;
    }
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::setUniformMatrix(const char* name, glm::mat2 value){
    // Ensure program is active before setting uniforms
    activate();
    int location = glGetUniformLocation(ID, name);
    
    if (location == -1){
        std::cout << "(!) WARNING: uniform '" << name << "' not found in shader program" << std::endl;
        return;
    }
    glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));
}