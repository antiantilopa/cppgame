#include "include/core_geometry.h"
#include "GLFW/glfw3.h"
#include <iostream>


namespace CppGame {

Shader* CoreGeometry::shader2d_ptr = nullptr;
Shader* CoreGeometry::shader3d_ptr = nullptr;
Shader* CoreGeometry::light_shader3d_ptr = nullptr;
Shader* CoreGeometry::billboard_shader3d_ptr = nullptr;
VAO* CoreGeometry::vao2d_ptr = nullptr;
VAO* CoreGeometry::vao3d_ptr = nullptr;
VBO* CoreGeometry::vbo2d_ptr = nullptr;
VBO* CoreGeometry::vbo3d_ptr = nullptr;
EBO* CoreGeometry::ebo_square_ptr = nullptr;
EBO* CoreGeometry::ebo_line2d_ptr = nullptr;
EBO* CoreGeometry::ebo_cube_ptr = nullptr;
EBO* CoreGeometry::ebo_line3d_ptr = nullptr;
std::filesystem::path CoreGeometry::PATH = "";

void CoreGeometry::init(){
    CoreGeometry::PATH = std::filesystem::current_path() / "cppgame";
    // say glfw what version of OpenGL we will use
    // version is 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 3.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //  .3

    // CORE profile means the program uses "modern" things
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int initialized_correctly;
    // initialie GLFW
    initialized_correctly = glfwInit();
    if (initialized_correctly == GLFW_FALSE){
        std::cout << "(!!!) ERROR: glfwInit() failed!\n";
        throw std::invalid_argument("something gone wrong ahh error");
    }
}

}