#include <iostream>

#include "include/window.h"
#include "include/mode.h"

Window::Window(int width, int height, const char* title, bool fullscreen){
    // create window with GLFW
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    if (fullscreen){
        window = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), NULL);
    }
    else{
        window = glfwCreateWindow(width, height, title, NULL, NULL);
    }
    
    if (window == NULL){
        std::cout << "Error occured during window creation.\n";
        throw "something gone wrong ahh error";
    }
    // Adds window into context, and makes it current
    // (whatever it means)
    glfwMakeContextCurrent(window);

    // initialie GLAD for OpenGL
    // (!) always AFTER window is created and in context (!)
    int initialized_correctly = gladLoadGL();
    if (initialized_correctly == GL_FALSE){
        std::cout << "(!!!) ERROR: gladLoadGL() failed!\n";
        throw "something gone wrong ahh error";
    }
    // Tell OpenGL what part of screen to use
    glViewport(0, 0, width, height);
    this->width = width;
    this->height = height;
}

Window::~Window(){
    glfwDestroyWindow(window);
}

bool Window::exitPressed(){
    return glfwWindowShouldClose(window);
}

void Window::flip(){
    glfwSwapBuffers(window);
}

void Window::fill(unsigned int r, unsigned int g, unsigned int b, unsigned int a){
    glClearColor((float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f, (float) a / 255.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}