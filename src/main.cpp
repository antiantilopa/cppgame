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
#include <stdexcept>

#include "cppgame/include/cppgame.h"
#include "cppgame/include/VAO.h"
#include "cppgame/include/VBO.h"
#include "cppgame/include/EBO.h"
#include "cppgame/include/window.h"
#include "cppgame/include/shader.h"
#include "cppgame/include/camera.h"

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

    Camera camera = Camera();
    camera.const_up = false;
    camera.setPosition(glm::vec3(0.0f, -0.5f, -2.0f));
    
    Mode::setOrigin(Mode::ORIGIN_CENTER);
    Mode::setDirection(Mode::DIRECTION_DOWN_RIGHT);
    
    Texture image("deleteme/image.png");
    Texture texture("deleteme/texture.png");
    Texture background("deleteme/background.png");
    
    bool first_click = true;
    int x, y;
    int tick = 0;
    float speed = 2.0f;
    float sensitivity = 7.0f;
    float rotx, roty, rotz;
    double fps;
    glfwSwapInterval(1);
    auto last_time = std::chrono::steady_clock::now();

    Model scroll = Model("deleteme/scroll/scene.gltf");
    Model plane = Model("deleteme/plane/scene.gltf");

    while (!window.exitPressed()){
        CppGame::shader3d_ptr->activate();
        CppGame::shader3d_ptr->setUniform("light_color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        CppGame::shader3d_ptr->setUniform("light_pos", camera.getPos());
        
        auto current_time = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = current_time - last_time;
        last_time = current_time;
        
        if (glfwGetKey(CppGame::window_ptr->window, GLFW_KEY_W)){
            camera.updatePosition(camera.getForward() * speed * elapsed.count());
        }
        if (glfwGetKey(CppGame::window_ptr->window, GLFW_KEY_S)){
            camera.updatePosition(-camera.getForward() * speed * elapsed.count());
        }
        if (glfwGetKey(CppGame::window_ptr->window, GLFW_KEY_D)){
            camera.updatePosition(camera.getRight() * speed * elapsed.count());
        }
        if (glfwGetKey(CppGame::window_ptr->window, GLFW_KEY_A)){
            camera.updatePosition(-camera.getRight() * speed * elapsed.count());
        }
        if (glfwGetKey(CppGame::window_ptr->window, GLFW_KEY_SPACE)){
            camera.updatePosition(camera.getUp() * speed * elapsed.count());
        }
        if (glfwGetKey(CppGame::window_ptr->window, GLFW_KEY_LEFT_SHIFT)){
            camera.updatePosition(-camera.getUp() * speed * elapsed.count());
        }
        if (glfwGetKey(CppGame::window_ptr->window, GLFW_KEY_Q)){
            rotz = -sensitivity * elapsed.count() * 7;
        }
        if (glfwGetKey(CppGame::window_ptr->window, GLFW_KEY_E)){
            rotz = sensitivity * elapsed.count() * 7;
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
                rotx = -sensitivity * y * elapsed.count();
                roty = -sensitivity * x * elapsed.count();
            }
        }
        else{
            first_click = false;
            glfwSetInputMode(window.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        
        camera.updateOrientation(rotx, roty, rotz);
        rotx = 0.0f;
        roty = 0.0f;
        rotz = 0.0f;
        // clear all events 
        glfwPollEvents();
        
        // sets background color for clear or swap
        window.fill(64, 0, 64, 255);

        CppGame::Draw2D::texture(0, 0, background, tick / 16, tick / 16, camera.getPos().x);
        tick++;
        CppGame::Draw3D::piramid(4, 4, 0, 1, 1, 1, 200, 10, 20);
        CppGame::Draw3D::cube(4, 2, 0, 1, 1, 1, 200, 10, 100);
        CppGame::Draw3D::cube(4, 0, 0, 1, 1, 1, 10, 10, 200);
        CppGame::Draw3D::cube(4, -2, 0, 100, 1, 100, 200, 200, 200);
        CppGame::Draw3D::billboard(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 2.0f), image);
        plane.draw(*CppGame::shader3d_ptr, camera, glm::vec3(0.0f, 2.0f, 0.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f));
        scroll.draw(*CppGame::shader3d_ptr, camera, glm::vec3(0.0f, 2.0f, 4.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(-0.01f, -0.01f, -0.01f));
        if (glGetError() == GL_INVALID_OPERATION){
            std::cout << "this is written once btw flag 1\n";
            throw std::runtime_error("FUCK!!!!");
        }

        // swaps two image buffers.
        window.flip();
        if (glGetError() == GL_INVALID_OPERATION){
            std::cout << "FVCK\n";
        }
        // fps = (double) 1 / elapsed.count();
        // std::cout << fps << "\n";
    }

    // we need to terminate glfw
    glfwTerminate();

    // Actually, it is not nessecary to clean-up, but it is recomneded.
    return 0;
}