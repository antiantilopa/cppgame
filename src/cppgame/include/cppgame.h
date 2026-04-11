#ifndef CPPGAME_H
#define CPPGAME_H

#include "shader.h"
#include "window.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "mode.h"
#include "texture.h"
#include "model.h"

#include <string>
#include <filesystem>

class CppGame{
public:
    static Shader* shader1_ptr;
    static Shader* shader2_ptr;
    static Window* window_ptr;
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

    class Draw2D{
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
        static void texture(int x, int y, Texture& texture, char red = 255, char green = 255, char blue = 255);
        static void texture(int x, int y, Texture& texture, char color[3] = nullptr);
    };
    class Draw3D{
    public:
        static void init(Window& window);
        static void cube(int x, int y, int z, int width, int height, int depth, char red, char green, char blue, int border_width=-1);
        static void cube(int x, int y, int z, int width, int height, int depth, char color[3], int border_width=-1);
        static void cube(int cube_value[6], char red, char green, char blue, int border_width=-1);
        static void cube(int cube_value[6], char color[3], int border_width=-1);
        static void line(int x1, int y1, int z1, int x2, int y2, int z2, char red, char green, char blue, int width=1);
        static void line(int x1, int y1, int z1, int x2, int y2, int z2, char color[3], int width=1);
        static void line(int line_value[6], char red, char green, char blue, int width=1);
        static void line(int line_value[6], char color[3], int width=1);
        static void model(int x, int y, int z, Model& model, char red = 255, char green = 255, char blue = 255);
        static void model(int x, int y, int z, Model& model, char color[3] = nullptr);
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