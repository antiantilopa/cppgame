#include "include/cppgame.h"
#include "GLFW/glfw3.h"
#include <iostream>

Shader* CppGame::shader1_ptr = nullptr;
Shader* CppGame::shader2_ptr = nullptr;
Window* CppGame::window_ptr = nullptr;
VAO* CppGame::vao2d_ptr = nullptr;
VAO* CppGame::vao3d_ptr = nullptr;
VBO* CppGame::vbo2d_ptr = nullptr;
VBO* CppGame::vbo3d_ptr = nullptr;
EBO* CppGame::ebo_square_ptr = nullptr;
EBO* CppGame::ebo_line2d_ptr = nullptr;
EBO* CppGame::ebo_cube_ptr = nullptr;
EBO* CppGame::ebo_line3d_ptr = nullptr;
std::filesystem::path CppGame::PATH = "";

void CppGame::init(){
    CppGame::PATH = std::filesystem::path(__FILE__).parent_path();
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
void CppGame::Mouse::getPosition(T* x, T* y){
    double x_pos, y_pos;
    glfwGetCursorPos(window_ptr->window, &x_pos, &y_pos);
    
    *x = (T) Mode::x_sign * (x_pos - Mode::ox * window_ptr->width / 2);
    *y = -((T) Mode::y_sign * (y_pos - Mode::oy * window_ptr->height / 2));
}

template void CppGame::Mouse::getPosition<int>(int* x, int* y);
template void CppGame::Mouse::getPosition<float>(float* x, float* y);
template void CppGame::Mouse::getPosition<double>(double* x, double* y);

template<typename T>
T* CppGame::Mouse::getPosition(){
    double x_pos, y_pos;
    glfwGetCursorPos(window_ptr->window, &x_pos, &y_pos);
    T* position = new T[2];
    position[0] = (T) Mode::x_sign * (x_pos - Mode::ox * window_ptr->width / 2);
    position[1] = -((T) Mode::y_sign * (y_pos - Mode::oy * window_ptr->height / 2));
    return position;
}

template int* CppGame::Mouse::getPosition<int>();
template float* CppGame::Mouse::getPosition<float>();
template double* CppGame::Mouse::getPosition<double>();

template<typename T>
void CppGame::Mouse::getPosition(T* position){
    double x_pos, y_pos;
    glfwGetCursorPos(window_ptr->window, &x_pos, &y_pos);
    position[0] = (T) Mode::x_sign * (x_pos - Mode::ox * window_ptr->width / 2);
    position[1] = -((T) Mode::y_sign * (y_pos - Mode::oy * window_ptr->height / 2));
}

template void CppGame::Mouse::getPosition<int>(int* position);
template void CppGame::Mouse::getPosition<float>(float* position);
template void CppGame::Mouse::getPosition<double>(double* position);

template<typename T>
void CppGame::Mouse::setPosition(T x, T y){
    double x_pos = (double)(x * Mode::x_sign + Mode::ox * window_ptr->width / 2);
    double y_pos = (double)(-y * Mode::y_sign + Mode::oy * window_ptr->height / 2);
    glfwSetCursorPos(window_ptr->window, x_pos, y_pos);
}

template void CppGame::Mouse::setPosition<int>(int x, int y);
template void CppGame::Mouse::setPosition<float>(float x, float y);
template void CppGame::Mouse::setPosition<double>(double x, double y);

template<typename T>
void CppGame::Mouse::setPosition(T* position){
    double x_pos = (double)(position[0] * Mode::x_sign + Mode::ox * window_ptr->width / 2);
    double y_pos = (double)(-position[1] * Mode::y_sign + Mode::oy * window_ptr->height / 2);
    glfwSetCursorPos(window_ptr->window, x_pos, y_pos);
}

template void CppGame::Mouse::setPosition<int>(int* position);
template void CppGame::Mouse::setPosition<float>(float* position);
template void CppGame::Mouse::setPosition<double>(double* position);