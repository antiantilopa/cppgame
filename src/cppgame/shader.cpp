#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cmath>
#include <vector>

#include <glad/glad.h>

#include "include/shader.h"


const char* getShader(const std::string& path){
    std::ifstream in(path, std::ios::in);
    if (!in) {
        throw std::runtime_error("Failed to open file: " + path);
    }
    char x;
    char* result = new char[16];
    unsigned int capacity = 16;
    unsigned int len = 0;
    while (in >> std::noskipws >> x){
        result[len] = x;
        len++;
        if (len == capacity){
            char* temp = new char[capacity * 2];
            std::memcpy(temp, result, capacity);
            delete[] result;
            result = temp;
            capacity *= 2;
        }
    }
    result[len] = '\0';

    in.close();
    return (const char*) result;
}

Shader::Shader(const char* vertex_shader_file, const char* fragment_shader_file){
    this->compiled_correctly = true;
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    int compiled_correctly;
    int maxLength = 0;
    const char* vertex_shader_src = getShader(vertex_shader_file);
    glShaderSource(vertex_shader, 1, &vertex_shader_src, NULL);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compiled_correctly);
    if (compiled_correctly == GL_FALSE){
        this->compiled_correctly = false;
        glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &maxLength);
        char* errorLog = new char[maxLength];
        glGetShaderInfoLog(vertex_shader, maxLength, &maxLength, &errorLog[0]);
        std::cout << "(!) ERROR: vertex shader compilation failed:\n" << &errorLog[0] << std::endl;
        delete[] errorLog;
    }

    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragment_shader_src = getShader(fragment_shader_file);
    glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compiled_correctly);
    if (compiled_correctly == GL_FALSE){
        this->compiled_correctly = false;
        glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &maxLength);
        char* errorLog = new char[maxLength];
        glGetShaderInfoLog(fragment_shader, maxLength, &maxLength, &errorLog[0]);
        std::cout << "(!) ERROR: fragment shader compilation failed:\n" << &errorLog[0] << std::endl;
        delete[] errorLog;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex_shader);
    glAttachShader(ID, fragment_shader);

    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &compiled_correctly);
    if (compiled_correctly == GL_FALSE){
        this->compiled_correctly = false;
        glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &maxLength);
        char* errorLog = new char[maxLength];
        glGetProgramInfoLog(ID, maxLength, &maxLength, &errorLog[0]);
        std::cout << "(!) ERROR: shader program linking failed:\n" << &errorLog[0] << std::endl;
        delete[] errorLog;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    delete[] vertex_shader_src;
    delete[] fragment_shader_src;
}

Shader::Shader(const std::filesystem::path& vertex_shader_file, const std::filesystem::path& fragment_shader_file) : Shader(vertex_shader_file.string().c_str(), fragment_shader_file.string().c_str()){}
Shader::Shader(const std::string& vertex_shader_file, const std::string& fragment_shader_file) : Shader(vertex_shader_file.c_str(), fragment_shader_file.c_str()){}

Shader::~Shader(){
    glDeleteProgram(ID);
}

void Shader::activate(){
    glUseProgram(ID);
}

template<typename T>
void Shader::setUniform(const char* name, T* value_ptr, int dim){
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
    } else {
        std::cout << "(!) ERROR: uniform of given type not supported" << std::endl;
    }
}

template void Shader::setUniform<float>(const char* name, float value);
template void Shader::setUniform<int>(const char* name, int value);
template void Shader::setUniform<unsigned int>(const char* name, unsigned int value);