#include "include/cppgame.h"
#include "GLFW/glfw3.h"
#include <iostream>

float vertices_square[] =
{
    -1.0f, -1.0f,
    1.0f, -1.0f,
    1.0f, 1.0f,
    -1.0f, 1.0f,
};
unsigned int indices_square[] =
{
    0, 1, 2,
    0, 3, 2,
};
unsigned int indices_line2d[] =
{
    0, 2,
};

int const SQUARE_TYPE = 0;
int const LINE_TYPE = 1; 
int const TEXTURE_TYPE = 2; 

void CppGame::Draw2D::init(Window& window){
    // (!) Here ordering is VERY important, first we make VAO, then VBO (!)
    VAO& vao = *new VAO();
    vao.bind();

    VBO& vbo = *new VBO(vertices_square, sizeof(vertices_square));

    EBO& ebo_square = *new EBO(indices_square, sizeof(indices_square));
    EBO& ebo_line = *new EBO(indices_line2d, sizeof(indices_line2d));

    // Here GL_STATIC_DRAW says that we want them to be drawn, and we will not change verticies.
    vao.LinkVBO(vbo, 0, 2, GL_FLOAT, 2 * sizeof(float), 0);

    // clear up, so VBO and VAO are not used again
    // (!) The order is  important (!)
    vao.unbind();
    vbo.unbind();
    ebo_square.unbind();
    ebo_line.unbind();
    Shader& shader_program = *new Shader(CppGame::PATH / "shaders/default2d.vert", CppGame::PATH / "shaders/default2d.frag");
    if (!shader_program.compiled_correctly){
        std::cout << "(!!!) ERROR: shader compilation failed!\n";
        throw "something gone wrong ahh error";
    }
    shader_program.activate();
    shader_program.setUniform("window_width", (float)window.width);
    shader_program.setUniform("window_height", (float)window.height);

    shader1_ptr = &shader_program;
    window_ptr = &window;
    vao2d_ptr = &vao;
    vbo2d_ptr = &vbo;
    ebo_square_ptr = &ebo_square;
    ebo_line2d_ptr = &ebo_line;

}

void CppGame::Draw2D::rect(int x, int y, int width, int height, char red, char green, char blue, int border_width){
    if (border_width * 2 >= width || border_width * 2 >= height){
        border_width = -1;
    }
    if (border_width >= 0){
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    float color[3] = {(float)(unsigned char)red / 255.0f, (float)(unsigned char)green / 255.0f, (float)(unsigned char)blue / 255.0f};
    shader1_ptr->activate();
    shader1_ptr->setUniform("width", (float)width);
    shader1_ptr->setUniform("height", (float)height);
    shader1_ptr->setUniform("x", (float)(x + (Mode::ox - 1) * (window_ptr->width) / 2) * Mode::x_sign - (Mode::ox - 1) * (width / 2));
    shader1_ptr->setUniform("y", (float)(y - (Mode::oy - 1) * (window_ptr->height) / 2) * Mode::y_sign + (Mode::oy - 1) * (height / 2));
    shader1_ptr->setUniform("color", color, 3);
    shader1_ptr->setUniform("border_width", (float)border_width);
    shader1_ptr->setUniform("shape_type", SQUARE_TYPE);

    vao2d_ptr->bind();
    vbo2d_ptr->bind();
    ebo_square_ptr->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
    vao2d_ptr->unbind();
    vbo2d_ptr->unbind();
    ebo_square_ptr->unbind();
    if (border_width >= 0){
        glDisable(GL_BLEND);
    }
}

void CppGame::Draw2D::rect(int x, int y, int width, int height, char color[3], int border_width){
    rect(x, y, width, height, color[0], color[1], color[2], border_width);
}

void CppGame::Draw2D::rect(int rect_value[4], char red, char green, char blue, int border_width){
    rect(rect_value[0], rect_value[1], rect_value[2], rect_value[3], red, green, blue, border_width);
}

void CppGame::Draw2D::rect(int rect_value[4], char color[3], int border_width){
    rect(rect_value[0], rect_value[1], rect_value[2], rect_value[3], color[0], color[1], color[2], border_width);
}

void CppGame::Draw2D::line(int x1, int y1, int x2, int y2, char red, char green, char blue, int width){
    float color[3] = {(float)(unsigned char)red / 255.0f, (float)(unsigned char)green / 255.0f, (float)(unsigned char)blue / 255.0f};
    shader1_ptr->activate();
    shader1_ptr->setUniform("x", (float)(x1 + (Mode::ox - 1) * (window_ptr->width) / 2) * Mode::x_sign);
    shader1_ptr->setUniform("y", (float)(y1 - (Mode::oy - 1) * (window_ptr->height) / 2) * Mode::y_sign);
    shader1_ptr->setUniform("x2", (float)(x2 + (Mode::ox - 1) * (window_ptr->width) / 2) * Mode::x_sign);
    shader1_ptr->setUniform("y2", (float)(y2 - (Mode::oy - 1) * (window_ptr->height) / 2) * Mode::y_sign);
    shader1_ptr->setUniform("color", color, 3);
    shader1_ptr->setUniform("shape_type", LINE_TYPE);

    glLineWidth((float)width);

    vao2d_ptr->bind();
    vbo2d_ptr->bind();
    ebo_line2d_ptr->bind();
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)0);
    vao2d_ptr->unbind();
    vbo2d_ptr->unbind();
    ebo_line2d_ptr->unbind();
}

void CppGame::Draw2D::line(int x1, int y1, int x2, int y2, char color[3], int width){
    line(x1, y1, x2, y2, color[0], color[1], color[2], width);
}

void CppGame::Draw2D::line(int line_value[4], char red, char green, char blue, int width){
    line(line_value[0], line_value[1], line_value[2], line_value[3], red, green, blue, width);
}

void CppGame::Draw2D::line(int line_value[4], char color[3], int width){
    line(line_value[0], line_value[1], line_value[2], line_value[3], color[0], color[1], color[2], width);
}

void CppGame::Draw2D::texture(int x, int y, Texture& texture, char red, char green, char blue){
    float color[3] = {(float)(unsigned char)red / 255.0f, (float)(unsigned char)green / 255.0f, (float)(unsigned char)blue / 255.0f};
    if (texture.channel_num == 4){
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    shader1_ptr->activate();
    shader1_ptr->setUniform("x", (float)(x + (Mode::ox - 1) * (window_ptr->width) / 2) * Mode::x_sign - (Mode::ox - 1) * (texture.width / 2));
    shader1_ptr->setUniform("y", (float)(y - (Mode::oy - 1) * (window_ptr->height) / 2) * Mode::y_sign + (Mode::oy - 1) * (texture.height / 2));
    shader1_ptr->setUniform("color", color, 3);
    shader1_ptr->setUniform("width", (float)texture.width);
    shader1_ptr->setUniform("height", (float)texture.height);
    shader1_ptr->setUniform("texture1", 0);
    shader1_ptr->setUniform("shape_type", TEXTURE_TYPE);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    vao2d_ptr->bind();
    vbo2d_ptr->bind();
    ebo_square_ptr->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
    vao2d_ptr->unbind();
    vbo2d_ptr->unbind();
    ebo_square_ptr->unbind();
}

void CppGame::Draw2D::texture(int x, int y, Texture& texture, char color[3]){
    if (color == nullptr){
        Draw2D::texture(x, y, texture, 255, 255, 255);
    }
    Draw2D::texture(x, y, texture, color[0], color[1], color[2]);
}
