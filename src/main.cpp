#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <stb/stb_image.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cmath>
#include <vector>
#include <chrono>

#include "cppgame/include/cppgame.h"
#include "cppgame/include/VAO.h"
#include "cppgame/include/VBO.h"
#include "cppgame/include/EBO.h"
#include "cppgame/include/window.h"
#include "cppgame/include/shader.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <glm/gtx/string_cast.hpp>
int WIDTH = 800;
int HEIGHT = 600;

int offset[] = {0, 0};
int x, y;

int abs(int x){
    if (x < 0){
        return -x;
    }
    return x;
}

float rotation = 0.0f;

int main(){
    CppGame::init();
    Window window = Window(WIDTH, HEIGHT, "title");
    
    CppGame::Draw2D::init(window);
    CppGame::Draw3D::init(window);

    Mode::setOrigin(Mode::ORIGIN_CENTER);
    Mode::setDirection(Mode::DIRECTION_DOWN_RIGHT);

    std::cout << (int)Mode::ox << " " << (int)Mode::oy << " " << (int)Mode::x_sign << " " << (int)Mode::y_sign << "\n";
    std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "\n";

    Texture texture("deleteme/image.png");
    std::cout << texture.width << " " << texture.height << "\n";
    std::cout << abs(-1) << " " << abs(-203) << "\n";

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
    proj = glm::perspective(glm::radians(45.0f), (float) WIDTH / HEIGHT, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetAttribLocation(CppGame::shader2_ptr->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetAttribLocation(CppGame::shader2_ptr->ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetAttribLocation(CppGame::shader2_ptr->ID, "proj"), 1, GL_FALSE, glm::value_ptr(proj));

    std::printf(glm::to_string(proj * view * model * glm::vec4(-1, -1, -1, 1)).c_str());
    std::cout << "\n";
    std::printf(glm::to_string(proj * view * model * glm::vec4(-1, -1, 1, 1)).c_str());
    std::cout << "\n";
    std::printf(glm::to_string(proj * view * model * glm::vec4(-1, 1, -1, 1)).c_str());
    std::cout << "\n";

    while (!window.exitPressed()){
        if (glfwGetKey(CppGame::window_ptr->window, GLFW_KEY_W)){
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -0.1f));
        }
        if (glfwGetKey(CppGame::window_ptr->window, GLFW_KEY_S)){
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.1f));
        }
        if (glfwGetKey(CppGame::window_ptr->window, GLFW_KEY_A)){
            view = glm::translate(view, glm::vec3(-0.1f, 0.0f, 0.0f));
        }
        if (glfwGetKey(CppGame::window_ptr->window, GLFW_KEY_D)){
            view = glm::translate(view, glm::vec3(0.1f, 0.0f, 0.1f));
        }
        if (glfwGetKey(CppGame::window_ptr->window, GLFW_KEY_SPACE)){
            view = glm::translate(view, glm::vec3(0.0f, 0.1f, 0.0f));
        }
        if (glfwGetKey(CppGame::window_ptr->window, GLFW_KEY_LEFT_SHIFT)){
            view = glm::translate(view, glm::vec3(0.0f, -0.1f, 0.0f));
        }
        // std::printf(glm::to_string(view * glm::vec4(0, 0, 0, 1)).c_str());
        // std::cout << "\n";
        // clear all events 
        glfwPollEvents();
        
        // sets background color for clear or swap
        // window.fill(64, 0, 64, 255);
        
        CppGame::Mouse::getPosition(&x, &y);
        offset[0] = x;
        offset[1] = y;

        // CppGame::Draw2D::rect(offset[0], offset[1], 100, 100, 255, 0, 0, 10);
        // CppGame::Draw2D::line(offset[0] + 50, offset[1] + 50, offset[0] - 50, offset[1] - 50, 0, 0, 0, 10);
        // CppGame::Draw2D::line(offset[0] + 50, offset[1] - 50, offset[0] - 50, offset[1] + 50, 200, 200, 200, 10);
        // CppGame::Draw2D::texture(0, 0, texture, abs(offset[0] % 510 - 255), abs(offset[1] % 510 - 255), 128);

        CppGame::Draw3D::cube(0, 0, 0, 1, 1, 1, 200, 200, 200);

        // swaps two image buffers.
        window.flip();
    }

    // we need to terminate glfw
    glfwTerminate();

    // Actually, it is not nessecary to clean-up, but it is recomneded.
    return 0;
}