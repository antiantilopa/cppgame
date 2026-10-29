#pragma once

#include "cppgame.h"

namespace CppGame {

class Draw2D{
public:
    static void init();
    static void rect(int x, int y, int width, int height, char red, char green, char blue, int border_width=-1, Shader* shader = nullptr);
    static void rect(int x, int y, int width, int height, char color[3], int border_width=-1, Shader* shader = nullptr);
    static void rect(int rect_value[4], char red, char green, char blue, int border_width=-1, Shader* shader = nullptr);
    static void rect(int rect_value[4], char color[3], int border_width=-1, Shader* shader = nullptr);
    static void line(int x1, int y1, int x2, int y2, char red, char green, char blue, int width=1, Shader* shader = nullptr);
    static void line(int x1, int y1, int x2, int y2, char color[3], int width=1, Shader* shader = nullptr);
    static void line(int line_value[4], char red, char green, char blue, int width=1, Shader* shader = nullptr);
    static void line(int line_value[4], char color[3], int width=1, Shader* shader = nullptr);
    static void texture(int x, int y, Texture& texture, char red = 255, char green = 255, char blue = 255, int size = 1, Shader* shader = nullptr);
    static void texture(int x, int y, Texture& texture, char color[3] = nullptr, int size = 1, Shader* shader = nullptr);
};

}