#ifndef TEXTURE_H
#define TEXTURE_H

#include <filesystem>
#include <string>
#include "shader.h"

class Texture{
public:
    unsigned int ID;
    int width, height, channel_num;
    const char* type;
    static const unsigned int LINEAR;
    static const unsigned int NEAREST;
    static const unsigned int REPEAT;
    static const unsigned int CLAMP_TO_EDGE;
    Texture(const char* image_path, unsigned int filter = NEAREST, unsigned int wrap = CLAMP_TO_EDGE, const char* type = "diffuse");
    Texture(std::filesystem::path& image_path, unsigned int filter = NEAREST, unsigned int wrap = CLAMP_TO_EDGE, const char* type = "diffuse");
    Texture(std::string& image_path, unsigned int filter = NEAREST, unsigned int wrap = CLAMP_TO_EDGE, const char* type = "diffuse");
    void bind();
    void unbind();
    void texUnit(Shader& shader, const char* uniform, unsigned int unit);
};



#endif