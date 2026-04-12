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
#include "glm/gtx/string_cast.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

int WIDTH = 800;
int HEIGHT = 600;

int abs(int x){
    if (x < 0){
        return -x;
    }
    return x;
}


int main(){
    CppGame::init();
    Window window = Window(WIDTH, HEIGHT, "title");
    
    CppGame::Draw3D::init(window);
    CppGame::Draw2D::init(window);
    
    Mode::setOrigin(Mode::ORIGIN_CENTER);
    Mode::setDirection(Mode::DIRECTION_DOWN_RIGHT);
    
    std::cout << (int)Mode::ox << " " << (int)Mode::oy << " " << (int)Mode::x_sign << " " << (int)Mode::y_sign << "\n";
    std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "\n";
    
    Texture texture("deleteme/image.png");
    std::cout << texture.width << " " << texture.height << "\n";
    std::cout << abs(-1) << " " << abs(-203) << "\n";
    
    
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 position = glm::vec3(0.0f, -0.5f, -2.0f);
    
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);
    bool first_click = true;
    int x, y;
    int tick = 0;
    // Assigns different transformations to each matrix
    proj = glm::perspective(glm::radians(45.0f), (float)WIDTH / HEIGHT, 0.1f, 100.0f);
    while (!window.exitPressed()){
        model = glm::rotate(model, glm::radians(0.001f), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::lookAt(position, position + orientation, up);
        int modelLoc = glGetUniformLocation(CppGame::shader2_ptr->ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(CppGame::shader2_ptr->ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projLoc = glGetUniformLocation(CppGame::shader2_ptr->ID, "proj");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
		// Outputs the matrices into the Vertex Shader

        if (glfwGetKey(CppGame::window_ptr->window, GLFW_KEY_W)){
            position += orientation * 0.001f;
        }
        if (glfwGetKey(CppGame::window_ptr->window, GLFW_KEY_S)){
            position -= orientation * 0.001f;
        }
        if (glfwGetKey(CppGame::window_ptr->window, GLFW_KEY_A)){
            position -= glm::normalize(glm::cross(orientation, up)) * 0.001f;
        }
        if (glfwGetKey(CppGame::window_ptr->window, GLFW_KEY_D)){
            position += glm::normalize(glm::cross(orientation, up)) * 0.001f;
        }
        if (glfwGetKey(CppGame::window_ptr->window, GLFW_KEY_SPACE)){
            position += up * 0.001f;
        }
        if (glfwGetKey(CppGame::window_ptr->window, GLFW_KEY_LEFT_SHIFT)){
            position -= up * 0.001f;
        }
        if (glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
            if (first_click){
                glfwSetInputMode(window.window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
                CppGame::Mouse::setPosition(0, 0);
                first_click = false;
            }
            else{
                CppGame::Mouse::getPosition(&x, &y);
                CppGame::Mouse::setPosition(0, 0);
                float rotx = -0.05f * x;
                float roty = -0.05f * y;
                orientation = glm::rotate(orientation, glm::radians(rotx), up);
                glm::vec3 new_orientation = glm::rotate(orientation, glm::radians(roty), glm::normalize(glm::cross(orientation, up)));

                // Decides whether or not the next vertical Orientation is legal or not
                if (abs(glm::angle(new_orientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
                {
                    orientation = new_orientation;
                }
            }
        }
        else{
            first_click = false;
            glfwSetInputMode(window.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        }
        // std::printf(glm::to_string(view * glm::vec4(0, 0, 0, 1)).c_str());
        // std::cout << "\n";
        // clear all events 
        glfwPollEvents();
        
        // sets background color for clear or swap
        window.fill(64, 0, 64, 255);
        


        CppGame::Draw2D::texture(0, 0, texture, tick / 16, tick / 16, 128);
        tick++;

        CppGame::Draw3D::cube(0, 0, 0, 1, 1, 1, 200, 200, 200);

        // swaps two image buffers.
        window.flip();
    }

    // we need to terminate glfw
    glfwTerminate();

    // Actually, it is not nessecary to clean-up, but it is recomneded.
    return 0;
}