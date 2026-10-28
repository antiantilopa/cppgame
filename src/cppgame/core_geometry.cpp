#include "include/core_geometry.h"
#include "GLFW/glfw3.h"
#include <iostream>


namespace CppGame {

Shader* CoreGeometry::shader2d_ptr = nullptr;
Shader* CoreGeometry::shader3d_ptr = nullptr;
Shader* CoreGeometry::light_shader3d_ptr = nullptr;
Shader* CoreGeometry::billboard_shader3d_ptr = nullptr;
Window* CoreGeometry::window_ptr = nullptr;
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
        throw "something gone wrong ahh error";
    }
}

template<typename T>
void CoreGeometry::Mouse::getPosition(T* x, T* y) {
    double x_pos, y_pos;
    glfwGetCursorPos(window_ptr->window, &x_pos, &y_pos);
    
    *x = (T) Mode::x_sign * (x_pos - Mode::ox * window_ptr->width / 2);
    *y = -((T) Mode::y_sign * (y_pos - Mode::oy * window_ptr->height / 2));
}

template void CoreGeometry::Mouse::getPosition<int>(int* x, int* y);
template void CoreGeometry::Mouse::getPosition<float>(float* x, float* y);
template void CoreGeometry::Mouse::getPosition<double>(double* x, double* y);

template<typename T>
T* CoreGeometry::Mouse::getPosition(){
    double x_pos, y_pos;
    glfwGetCursorPos(window_ptr->window, &x_pos, &y_pos);
    T* position = new T[2];
    position[0] = (T) Mode::x_sign * (x_pos - Mode::ox * window_ptr->width / 2);
    position[1] = -((T) Mode::y_sign * (y_pos - Mode::oy * window_ptr->height / 2));
    return position;
}

template int* CoreGeometry::Mouse::getPosition<int>();
template float* CoreGeometry::Mouse::getPosition<float>();
template double* CoreGeometry::Mouse::getPosition<double>();

template<typename T>
void CoreGeometry::Mouse::getPosition(T* position){
    double x_pos, y_pos;
    glfwGetCursorPos(window_ptr->window, &x_pos, &y_pos);
    position[0] = (T) Mode::x_sign * (x_pos - Mode::ox * window_ptr->width / 2);
    position[1] = -((T) Mode::y_sign * (y_pos - Mode::oy * window_ptr->height / 2));
}

template void CoreGeometry::Mouse::getPosition<int>(int* position);
template void CoreGeometry::Mouse::getPosition<float>(float* position);
template void CoreGeometry::Mouse::getPosition<double>(double* position);

template<typename T>
void CoreGeometry::Mouse::setPosition(T x, T y){
    double x_pos = (double)(x * Mode::x_sign + Mode::ox * window_ptr->width / 2);
    double y_pos = (double)(-y * Mode::y_sign + Mode::oy * window_ptr->height / 2);
    glfwSetCursorPos(window_ptr->window, x_pos, y_pos);
}

template void CoreGeometry::Mouse::setPosition<int>(int x, int y);
template void CoreGeometry::Mouse::setPosition<float>(float x, float y);
template void CoreGeometry::Mouse::setPosition<double>(double x, double y);

template<typename T>
void CoreGeometry::Mouse::setPosition(T* position){
    double x_pos = (double)(position[0] * Mode::x_sign + Mode::ox * window_ptr->width / 2);
    double y_pos = (double)(-position[1] * Mode::y_sign + Mode::oy * window_ptr->height / 2);
    glfwSetCursorPos(window_ptr->window, x_pos, y_pos);
}

template void CoreGeometry::Mouse::setPosition<int>(int* position);
template void CoreGeometry::Mouse::setPosition<float>(float* position);
template void CoreGeometry::Mouse::setPosition<double>(double* position);

}