#ifndef TEXTURE_H
#define TEXTURE_H

#include <filesystem>
#include <string>

class Texture{
public:
    unsigned int ID;
    int width, height, channel_num;
    static const unsigned int LINEAR;
    static const unsigned int NEAREST;
    static const unsigned int REPEAT;
    static const unsigned int CLAMP_TO_EDGE;
    Texture(const char* image_path, unsigned int filter = NEAREST, unsigned int wrap = CLAMP_TO_EDGE);
    Texture(std::filesystem::path& image_path, unsigned int filter = NEAREST, unsigned int wrap = CLAMP_TO_EDGE);
    Texture(std::string& image_path, unsigned int filter = NEAREST, unsigned int wrap = CLAMP_TO_EDGE);
    void bind();
    void unbind();
};



#endif