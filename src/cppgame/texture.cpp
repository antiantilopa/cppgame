#include "include/texture.h"

#include <stb/stb_image.h>
#include <iostream>
#include <glad/glad.h>

#define STBI_WINDOWS_UTF8

const unsigned int Texture::LINEAR = GL_LINEAR;
const unsigned int Texture::NEAREST = GL_NEAREST;
const unsigned int Texture::REPEAT = GL_REPEAT;
const unsigned int Texture::CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE;

Texture::Texture(const char* image_path, unsigned int filter, unsigned int wrap){
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(image_path, &width, &height, &channel_num, 0);
    if(!data){
        std::cout << "Failed to load texture: " << image_path << std::endl;
        std::cout << stbi_failure_reason() << std::endl;
        throw "Failed to load texture ahh error";
    }
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

    if(channel_num == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    else if(channel_num == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    else
        std::cout << "Unsupported number of channels: " << channel_num << std::endl;

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

Texture::Texture(std::filesystem::path& image_path, unsigned int filter, unsigned int wrap): Texture(image_path.string().c_str(), filter, wrap){}
Texture::Texture(std::string& image_path, unsigned int filter, unsigned int wrap): Texture(image_path.c_str(), filter, wrap){}

void Texture::bind(){
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}