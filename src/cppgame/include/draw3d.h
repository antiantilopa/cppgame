#pragma once

#include "cppgame.h"

namespace CppGame {
    class Draw3D{
        static Mesh* cube_mesh;
        static Mesh* piramid_mesh;
        static Mesh* nothing_mesh;
    public:
        static void init(Window& window);
        static void cube(int x, int y, int z, int width, int height, int depth, char red, char green, char blue, int border_width=-1);
        static void cube(int x, int y, int z, int width, int height, int depth, char color[3], int border_width=-1);
        static void cube(int cube_value[6], char red, char green, char blue, int border_width=-1);
        static void cube(int cube_value[6], char color[3], int border_width=-1);
        static void piramid(int x, int y, int z, int width, int height, int depth, char red, char green, char blue, int border_width=-1);
        static void piramid(int x, int y, int z, int width, int height, int depth, char color[3], int border_width=-1);
        static void piramid(int cube_value[6], char red, char green, char blue, int border_width=-1);
        static void piramid(int cube_value[6], char color[3], int border_width=-1);
        static void line(int x1, int y1, int z1, int x2, int y2, int z2, char red, char green, char blue, int width=1);
        static void line(int x1, int y1, int z1, int x2, int y2, int z2, char color[3], int width=1);
        static void line(int line_value[6], char red, char green, char blue, int width=1);
        static void line(int line_value[6], char color[3], int width=1);
        static void model(int x, int y, int z, Model& model, char red = 255, char green = 255, char blue = 255);
        static void model(int x, int y, int z, Model& model, char color[3] = nullptr);
        static void billboard(int x, int y, int z, float angle, int width, int height, Texture& texture);
        static void billboard(glm::vec3 pos, glm::vec3 direction, glm::vec2 size, Texture& texture);
    };
}    
