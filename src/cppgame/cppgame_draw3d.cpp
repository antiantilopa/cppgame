#include "include/cppgame.h"
#include <iostream>

float vertices_cube[] = {
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
};
float vertices_piramid[] = {
    -0.5f, 0.0f,  0.5f, 
	-0.5f, 0.0f, -0.5f, 
	 0.5f, 0.0f, -0.5f, 
	 0.5f, 0.0f,  0.5f, 
	 0.0f, 0.8f,  0.0f,
};
unsigned int indices_cube[] =
{
    0, 1, 2, 1, 2, 3,
    0, 2, 4, 2, 4, 6,
    0, 1, 4, 1, 4, 5,
    7, 6, 5, 6, 5, 4,
    7, 5, 3, 5, 3, 1,
    7, 6, 3, 6, 3, 2,
};
unsigned int indices_piramid[] = {
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

unsigned int indices_line3d[] = {
    0, 7
};

int const CUBE_TYPE = 0;

void CppGame::Draw3D::init(Window& window){
    VAO& vao = *new VAO();
    vao.bind();

    VBO& vbo = *new VBO(vertices_cube, sizeof(vertices_cube));

    EBO& ebo_cube = *new EBO(indices_cube, sizeof(indices_cube));
    EBO& ebo_line = *new EBO(indices_line3d, sizeof(indices_line3d));

    // Here GL_STATIC_DRAW says that we want them to be drawn, and we will not change verticies.
    vao.LinkVBO(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), 0);

    // clear up, so VBO and VAO are not used again
    // (!) The order is  important (!)
    vao.unbind();
    vbo.unbind();
    ebo_cube.unbind();
    ebo_line.unbind();
    Shader& shader_program = *new Shader(CppGame::PATH / "shaders/default3d.vert", CppGame::PATH / "shaders/default3d.frag");
    if (!shader_program.compiled_correctly){
        std::cout << "(!!!) ERROR: shader compilation failed!\n";
        throw "something gone wrong ahh error";
    }
    shader_program.activate();
    shader_program.setUniform("window_width", (float)window.width);
    shader_program.setUniform("window_height", (float)window.height);

    shader2_ptr = &shader_program;
    window_ptr = &window;
    vao3d_ptr = &vao;
    vbo3d_ptr = &vbo;
    ebo_cube_ptr = &ebo_cube;
    ebo_line3d_ptr = &ebo_line;
}

void CppGame::Draw3D::cube(int x, int y, int z, int width, int height, int depth, char red, char green, char blue, int border_width){
    glEnable(GL_DEPTH_TEST);
    if (border_width * 2 >= width || border_width * 2 >= height || border_width * 2 >= depth){
        border_width = -1;
    }
    if (border_width >= 0){
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    float color[3] = {(float)(unsigned char)red / 255.0f, (float)(unsigned char)green / 255.0f, (float)(unsigned char)blue / 255.0f};
    shader2_ptr->activate();
    shader2_ptr->setUniform("width", (float)width);
    shader2_ptr->setUniform("height", (float)height);
    shader2_ptr->setUniform("depth", (float)depth);
    shader2_ptr->setUniform("x", (float)x);
    shader2_ptr->setUniform("y", (float)y);
    shader2_ptr->setUniform("z", (float)z);
    shader2_ptr->setUniform("color", color, 3);

    vao3d_ptr->bind();
    vbo3d_ptr->bind();
    ebo_cube_ptr->bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
    vao3d_ptr->unbind();
    vbo3d_ptr->unbind();
    ebo_cube_ptr->unbind();
    if (border_width >= 0){
        glDisable(GL_BLEND);
    }
}