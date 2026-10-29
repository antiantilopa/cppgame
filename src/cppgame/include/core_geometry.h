#pragma once

#include "cppgame.h"

#include <string>
#include <filesystem>

namespace CppGame {

class CoreGeometry{
public:
    static Shader* shader2d_ptr;
    static Shader* shader3d_ptr;
    static Shader* light_shader3d_ptr;
    static Shader* billboard_shader3d_ptr;
    static VAO* vao2d_ptr;
    static VAO* vao3d_ptr;
    static VBO* vbo2d_ptr;
    static VBO* vbo3d_ptr;
    static EBO* ebo_square_ptr;
    static EBO* ebo_line2d_ptr;
    static EBO* ebo_cube_ptr;
    static EBO* ebo_line3d_ptr;

    static std::filesystem::path PATH;
    static void init();
};

}