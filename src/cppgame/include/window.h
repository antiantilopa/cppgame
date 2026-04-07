#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include "GLFW/glfw3.h"

class Window{
public:
    int width, height;
    GLFWwindow* window;

    Window(int width, int height, const char* title, bool fullscreen = false);
    ~Window();

    bool exitPressed();
    void flip(); // swaps buffers
    void fill(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
};

#endif