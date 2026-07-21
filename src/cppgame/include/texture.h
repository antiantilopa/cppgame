#ifndef TEXTURE_H
#define TEXTURE_H

#include <filesystem>
#include <string>
#include "shader.h"

class Texture{
public:
    unsigned int ID;
    int width, height, channel_num;
    unsigned int unit;
    const char* type;
    static const unsigned int LINEAR;
    static const unsigned int NEAREST;
    static const unsigned int REPEAT;
    static const unsigned int CLAMP_TO_EDGE;
    Texture(const char* image_path, const char* type = "diffuse", unsigned int unit = 0, unsigned int filter = NEAREST, unsigned int wrap = CLAMP_TO_EDGE);
    Texture(std::filesystem::path& image_path, const char* type = "diffuse", unsigned int unit = 0, unsigned int filter = NEAREST, unsigned int wrap = CLAMP_TO_EDGE);
    Texture(std::string& image_path, const char* type = "diffuse", unsigned int unit = 0, unsigned int filter = NEAREST, unsigned int wrap = CLAMP_TO_EDGE);
    void bind();
    void unbind();
    void texUnit(Shader& shader, const char* uniform, int unit = -1);
};



#endif