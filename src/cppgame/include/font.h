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
    void __raw_draw(std::string text, int x, int y, Shader& shader, int size = 1);
    void render(std::string text, Texture& output, int x, int y, Shader& shader, int size = 1);
    Texture& render(std::string text, Shader& shader);
};

