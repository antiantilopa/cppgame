#ifndef CPPGAME_H
#define CPPGAME_H

#include "shader.h"
#include "window.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "mode.h"

#include <string>
#include <filesystem>

class CppGame{
public:
    static Shader* shader1_ptr;
    static Window* window_ptr;
    static VAO* vao_ptr;
    static VBO* vbo_ptr;
    static EBO* ebo_square_ptr;
    static EBO* ebo_line_ptr;

    static std::filesystem::path PATH;
    static void init();

    class Draw{
    public:
        static void init(Window& window);
        static void rect(int x, int y, int width, int height, char red, char green, char blue, int border_width=-1);
        static void rect(int x, int y, int width, int height, char color[3], int border_width=-1);
        static void rect(int rect_value[4], char red, char green, char blue, int border_width=-1);
        static void rect(int rect_value[4], char color[3], int border_width=-1);
        static void line(int x1, int y1, int x2, int y2, char red, char green, char blue, int width=1);
        static void line(int x1, int y1, int x2, int y2, char color[3], int width=1);
        static void line(int line_value[4], char red, char green, char blue, int width=1);
        static void line(int line_value[4], char color[3], int width=1);
    };
    class Mouse{
    public:
        template<typename T>
        static void getPosition(T* x, T* y);
        template<typename T>
        static T* getPosition(); // creates new obhect on heap! needs deleting
        template<typename T>
        static void getPosition(T* position); // position has to be array of at least size 2.

        template<typename T>
        static void setPosition(T x, T y);
        template<typename T>
        static void setPosition(T* position); // position has to be array of at least size 2.
    };
};

#endif