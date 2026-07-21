#include "include/texture.h"

#include <stb/stb_image.h>
#include <iostream>
#include <glad/glad.h>

#define STBI_WINDOWS_UTF8

const unsigned int Texture::LINEAR = GL_LINEAR;
const unsigned int Texture::NEAREST = GL_NEAREST;
const unsigned int Texture::REPEAT = GL_REPEAT;
const unsigned int Texture::CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE;

Texture::Texture(const char* image_path, const char* type, unsigned int unit, unsigned int filter, unsigned int wrap){
    stbi_set_flip_vertically_on_load(true);
    this->unit = unit;
    unsigned char* data = stbi_load(image_path, &width, &height, &channel_num, 0);
    if(!data){
        std::cout << "Failed to load texture: " << image_path << std::endl;
        std::cout << stbi_failure_reason() << std::endl;
        throw "Failed to load texture ahh error";
    }
    this->type = type;
    glGenTextures(1, &ID);
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) std::cout << "Texture ctor - after glGenTextures error: " << err << "\n";
    glBindTexture(GL_TEXTURE_2D, ID);

    // ensure byte alignment for single-channel images
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    err = glGetError();
    if (err != GL_NO_ERROR) std::cout << "Texture ctor - after glBindTexture error: " << err << "\n";

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    err = glGetError();
    if (err != GL_NO_ERROR) std::cout << "Texture ctor - after glTexParameteri error: " << err << "\n";

    if(channel_num == 1)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
    else if(channel_num == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    else if(channel_num == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    else
        std::cout << "Unsupported number of channels: " << channel_num << std::endl;
    err = glGetError();
    if (err != GL_NO_ERROR) std::cout << "Texture ctor - after glTexImage2D error: " << err << "\n";

    glGenerateMipmap(GL_TEXTURE_2D);
    err = glGetError();
    if (err != GL_NO_ERROR) std::cout << "Texture ctor - after glGenerateMipmap error: " << err << "\n";
    stbi_image_free(data);
}

Texture::Texture(std::filesystem::path& image_path, const char* type, unsigned int unit, unsigned int filter, unsigned int wrap): Texture(image_path.string().c_str(), type, unit, filter, wrap){}
Texture::Texture(std::string& image_path, const char* type, unsigned int unit, unsigned int filter, unsigned int wrap): Texture(image_path.c_str(), type, unit, filter, wrap){}

void Texture::bind(){
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, int unit){
    // Interpret -1 as "use the texture's stored unit"
    if (unit == -1){
        unit = (int)this->unit;
    }
    else{
        this->unit = (unsigned int)unit;
    }

    // Ensure the shader program is active before querying or setting uniforms
    // Log and clear any pre-existing GL errors so they don't interfere
    GLenum before = glGetError();
    if (before != GL_NO_ERROR){
        std::cout << "Texture::texUnit - pre-existing GL error: " << before << "\n";
    }
    
    shader.activate();

    int texUni = glGetUniformLocation(shader.ID, uniform);
    if (texUni == -1){
        std::cout << "(!) WARNING: uniform '" << uniform << "' not found in shader program\n";
        return;
    }

    glUniform1i(texUni, unit);
    GLenum err = glGetError();
    if (err == GL_INVALID_OPERATION){
        std::cout << "Texture::texUnit - glUniform1i returned GL_INVALID_OPERATION\n";
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(shader.ID, GL_LINK_STATUS, &linkStatus);
        std::cout << "  shader link status: " << linkStatus << "\n";
        GLint infoLen = 0;
        glGetProgramiv(shader.ID, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 0){
            std::string log(infoLen, '\0');
            glGetProgramInfoLog(shader.ID, infoLen, NULL, &log[0]);
            std::cout << "  program info log:\n" << log << "\n";
        }
        // don't terminate the program; return so caller can continue
        return;
    }
}