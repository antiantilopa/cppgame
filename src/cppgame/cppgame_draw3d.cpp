#include "include/cppgame.h"
#include <iostream>

std::vector<Vertex3d> vertices_cube = {
    Vertex3d{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
    Vertex3d{glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
    Vertex3d{glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
    Vertex3d{glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 1.0f, 1.0f)},
    Vertex3d{glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
    Vertex3d{glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 0.0f, 1.0f)},
    Vertex3d{glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f)},
    Vertex3d{glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
};
std::vector<Vertex3d> vertices_piramid = {
    Vertex3d{glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(-0.5f, 0.0f,  0.5f)}, 
	Vertex3d{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(-0.5f, 0.0f, -0.5f)}, 
	Vertex3d{glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3( 0.5f, 0.0f, -0.5f), glm::vec3( 0.5f, 0.0f, -0.5f)}, 
	Vertex3d{glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3( 0.5f, 0.0f,  0.5f), glm::vec3( 0.5f, 0.0f,  0.5f)}, 
	Vertex3d{glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.0f, 0.8f,  0.0f)},
};
std::vector<unsigned int> indices_cube = {
    0, 1, 2, 1, 2, 3,
    0, 2, 4, 2, 4, 6,
    0, 1, 4, 1, 4, 5,
    7, 6, 5, 6, 5, 4,
    7, 5, 3, 5, 3, 1,
    7, 6, 3, 6, 3, 2,
};
std::vector<unsigned int> indices_piramid = {
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

std::vector<unsigned int> indices_line3d = {
    0, 7
};

int const CUBE_TYPE = 0;

void CppGame::Draw3D::init(Window& window){
    CppGame::cube = new Mesh(vertices_cube, Vertex3d::POS_NORMAL_COLOR, indices_cube);
    CppGame::piramid = new Mesh(vertices_piramid, Vertex3d::POS_NORMAL_COLOR, indices_piramid);
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
}

void CppGame::Draw3D::cube(int x, int y, int z, int width, int height, int depth, char red, char green, char blue, int border_width){
    glEnable(GL_DEPTH_TEST);
    float color[3] = {(float)(unsigned char)red / 255.0f, (float)(unsigned char)green / 255.0f, (float)(unsigned char)blue / 255.0f};
    shader2_ptr->activate();
    shader2_ptr->setUniform("width", (float)width);
    shader2_ptr->setUniform("height", (float)height);
    shader2_ptr->setUniform("depth", (float)depth);
    shader2_ptr->setUniform("x", (float)x);
    shader2_ptr->setUniform("y", (float)y);
    shader2_ptr->setUniform("z", (float)z);
    shader2_ptr->setUniform("color", color, 3);

    CppGame::cube->draw(*shader2_ptr);
}
void CppGame::Draw3D::cube(int x, int y, int z, int width, int height, int depth, char color[3], int border_width){
    CppGame::Draw3D::cube(x, y, z, width, height, depth, color[0], color[0], color[0], border_width);
}

void CppGame::Draw3D::cube(int cube_value[6], char red, char green, char blue, int border_width){
    CppGame::Draw3D::cube(cube_value[0], cube_value[1], cube_value[2], cube_value[3], cube_value[4], cube_value[5], red, green, blue, border_width);
}
void CppGame::Draw3D::cube(int cube_value[6], char color[3], int border_width){
    CppGame::Draw3D::cube(cube_value[0], cube_value[1], cube_value[2], cube_value[3], cube_value[4], cube_value[5], color[0], color[0], color[0], border_width);
}

void CppGame::Draw3D::piramid(int x, int y, int z, int width, int height, int depth, char red, char green, char blue, int border_width){
    glEnable(GL_DEPTH_TEST);
    float color[3] = {(float)(unsigned char)red / 255.0f, (float)(unsigned char)green / 255.0f, (float)(unsigned char)blue / 255.0f};
    shader2_ptr->activate();
    shader2_ptr->setUniform("width", (float)width);
    shader2_ptr->setUniform("height", (float)height);
    shader2_ptr->setUniform("depth", (float)depth);
    shader2_ptr->setUniform("x", (float)x);
    shader2_ptr->setUniform("y", (float)y);
    shader2_ptr->setUniform("z", (float)z);
    shader2_ptr->setUniform("color", color, 3);

    CppGame::piramid->draw(*shader2_ptr);
}
void CppGame::Draw3D::piramid(int x, int y, int z, int width, int height, int depth, char color[3], int border_width){
    CppGame::Draw3D::piramid(x, y, z, width, height, depth, color[0], color[0], color[0], border_width);
}

void CppGame::Draw3D::piramid(int piramid_value[6], char red, char green, char blue, int border_width){
    CppGame::Draw3D::piramid(piramid_value[0], piramid_value[1], piramid_value[2], piramid_value[3], piramid_value[4], piramid_value[5], red, green, blue, border_width);
}
void CppGame::Draw3D::piramid(int piramid_value[6], char color[3], int border_width){
    CppGame::Draw3D::piramid(piramid_value[0], piramid_value[1], piramid_value[2], piramid_value[3], piramid_value[4], piramid_value[5], color[0], color[0], color[0], border_width);
}