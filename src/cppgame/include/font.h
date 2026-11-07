#pragma once

#include "texture.h"
#include "fileopener.h"
#include "vertex.h"
#include "FBO.h"
#include "VAO.h"
#include "VBO.h"
#include "cppgame.h"
#include <filesystem>
#include <iostream>
#include <unordered_map>

// TODO this fuckery is bullshit that was made by me on game jam. redo this please
// basically, I have 2 files, .png that has the actual image, and .bin file
// in second file I store width height of characters, and where exactly they are on .png
// notice that cince width is unsigned char, max width and height of character is 255. not good
struct FontData{
    unsigned char char_width[256];
    unsigned char char_height[256];
    unsigned char char_offset_x[256];
    unsigned char char_offset_y[256];
}; 

class Font{
public:
    std::unordered_map<std::string, Texture*> cache;
    Texture* font_texture;
    FontData* font_data;
    static FBO* fbo;
    static VAO* vao;
    static VBO* vbo;
    static void init(); 
    Font(Texture& font_texture, FontData& font_data);
    Font(std::filesystem::path& font_path);
    Font(std::string& font_path);
    Font(const char* font_path);

    // draws without texture binding, port view changing, etc. 
    // TODO x, y does not match mode. current: TOP_LEFT RIGHT_DOWN (default opengl mode)
    void __raw_draw(std::string text, int x, int y, Shader& shader, int size = 1);

    // renders text onto the output texture with given parameters.
    // text can contain special characters: \n, \r, \t etc.
    // max text lenght 1024 characters
    void render(std::string text, Texture& output, int x, int y, Shader& shader, int size = 1);

    // creates new Texture object on heap, and stores pointer to the object in cache
    // renders text onto the new texture.
    // text can contain special characters: \n, \r, \t etc.
    // max text lenght 1024 characters
    // DO NOT USE THIS FOR DYNAMICALLY CHANGING TEXT.
    // use its overload that needs output texture provided
    Texture& render(std::string text, Shader& shader);

    void deleteTexture(Texture& texture); // deletes texture created on heap and discards it from cache.
    void deleteTexture(std::string text); // deletes texture created on heap with given text and discard it from cache.
    void deleteTexture(Texture& texture, std::string text); // deletes texture created on heap and discards it from cache. this is safest and fastest varian
};

