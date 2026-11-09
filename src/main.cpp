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

using namespace CppGame;

int WIDTH = 800;
int HEIGHT = 600;
int x, y;
float rotx = 0, roty = 0, rotz = 0;
float sensitivity = 2.0f;
std::chrono::duration<float> elapsed;
bool releasemouse = true;

glm::vec3 velocity{};

using namespace std;

void onrightclick(){
    std::cout << "iprem losum\n";
}

void onleftclick(){
    Mouse::hid();
    Mouse::setPosition(0, 0);
}


void onlefthold(unsigned long long t){
    Mouse::getPosition(&x, &y);
    Mouse::setPosition(0, 0);
    rotx += -sensitivity * y * elapsed.count();
    roty += -sensitivity * x * elapsed.count();
}

void onleftrelease(){
    if (releasemouse){
        Mouse::enable();
    }
}

void onleftdouble(unsigned long long t){
    if (releasemouse){
        Mouse::hid();
    }
    releasemouse = !releasemouse;
    std::cout << t  << " ";
}

std::string written_text = std::string();

void ontextinput(unsigned int key){
    if (key > 0xFF){
        return;
    }
    written_text.push_back(key);
}


int main(){
    // CoreGeometry::init();
    // Window window = Window(WIDTH, HEIGHT, "title");
    CppGame::OpenGLRenderer renderer = CppGame::OpenGLRenderer(WIDTH, HEIGHT, "title");
    // window.setAsMain();

    // pizdec: TODO HACK BUG:
    unsigned int RBO;
    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    Mouse::init();
    Mouse::setMinimalHoldTicks(10);
    Mouse::setMaximalTicksBetweenDoubleClick(20);

    Key::init();

    TextInput::init();

    Font::init();

    CppGame::Draw3D::init();
    CppGame::Draw2D::init();

    Camera camera = Camera();
    camera.const_up = false;
    camera.setPosition(glm::vec3(0.0f, -0.5f, -2.0f));
    
    Mode::setOrigin(Mode::ORIGIN_CENTER);
    Mode::setDirection(Mode::DIRECTION_DOWN_RIGHT);
    

    Texture image("deleteme/image.png");
    Texture texture("deleteme/texture.png");
    Texture background("deleteme/background.png");
    Texture text_input_texture = Texture(WIDTH, HEIGHT);
    Font font("deleteme/font.bin");

    Shader text_render_shader = Shader(
        CoreGeometry::PATH / "shaders/text_render2d.vert", 
        std::filesystem::path(),
        CoreGeometry::PATH / "shaders/text_render2d.frag"
    );
    text_render_shader.setUniform("window_width", (float) WIDTH);
    text_render_shader.setUniform("window_height", (float) HEIGHT);
    std::string text = "Test";
    Texture& text_tex = font.render(text, text_render_shader);

    bool first_click = true;
    int tick = 0;
    float speed = 5.0f;
    float acceleration = 3.0f;
    float friction = 0.98f;
    double fps;
    glfwSwapInterval(1);
    auto last_time = std::chrono::steady_clock::now();

    Model scroll = Model("deleteme/scroll/scene.gltf");
    Model plane = Model("deleteme/plane/scene.gltf");

    Mouse::setOnRightClick(onrightclick);
    
    Mouse::setOnLeftClick(onleftclick);
    Mouse::setOnLeftRelease(onleftrelease);
    Mouse::setOnLeftDoubleClick(onleftdouble);
    Mouse::setOnLeftHold(onlefthold);

    TextInput::setOnCharCallback(ontextinput);

    while (!Window::window_ptr->exitPressed()) {
        Mouse::update();
        CoreGeometry::shader3d_ptr->activate();
        CoreGeometry::shader3d_ptr->setUniform("light_color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        CoreGeometry::shader3d_ptr->setUniform("light_pos", camera.getPos());
        
        auto current_time = std::chrono::steady_clock::now();
        elapsed = current_time - last_time;
        last_time = current_time;
        camera.updatePosition(velocity * speed * elapsed.count());
        if (Key::isPressed(GLFW_KEY_W)){
            velocity += camera.getForward() * acceleration * elapsed.count();
        }
        if (Key::isPressed(GLFW_KEY_S)){
            velocity -= camera.getForward() * acceleration * elapsed.count();
        }
        if (Key::isPressed(GLFW_KEY_D)){
            velocity += camera.getRight() * acceleration * elapsed.count();
        }
        if (Key::isPressed(GLFW_KEY_A)){
            velocity -= camera.getRight() * acceleration * elapsed.count();
        }
        if (Key::isPressed(GLFW_KEY_SPACE)){
            velocity += camera.getUp() * acceleration * elapsed.count();
        }
        if (Key::isPressed(GLFW_KEY_LEFT_SHIFT)){
            velocity -= camera.getUp() * acceleration * elapsed.count();
        }
        velocity *= friction;
        if (Key::isPressed(GLFW_KEY_Q)){
            rotz = -sensitivity * elapsed.count() * 21.5f;
        }
        if (Key::isPressed(GLFW_KEY_E)){
            rotz = sensitivity * elapsed.count() * 21.5f;
        }
        if (!releasemouse){
            Mouse::getPosition(&x, &y);
            Mouse::setPosition(0, 0);
            rotx += -sensitivity * y * elapsed.count();
            roty += -sensitivity * x * elapsed.count();
        }

        camera.updateOrientation(rotx, roty, rotz);
        rotx *= friction;
        roty *= friction;
        rotz *= friction;
        // clear all events 
        glfwPollEvents();
        
        font.render(written_text, text_input_texture, 0, 0, text_render_shader, 1);
        CppGame::Draw2D::texture(0, 0, text_input_texture, tick / 16, tick / 16, camera.getPos().x);
        // sets background color for clear or swap
        renderer.predraw();
        Window::window_ptr->fill(255, 0, 0, 0); // fills the screen...
        
        CppGame::Draw2D::texture(0, 0, background, tick / 16, tick / 16, camera.getPos().x);
        

        tick++;
        text_tex.bind(); // VERY BAD THING!!! DO NOT BIND RANDOM TEXTURES IN RANDOM PLACES!!!
        CppGame::Draw3D::piramid(4, 4, 0, 1, 1, 1, 200, 10, 20);
        CppGame::Draw3D::cube(4, 2, 0, 1, 1, 1, 200, 10, 100);
        CppGame::Draw3D::cube(4, 0, 0, 1, 1, 1, 10, 10, 200);
        CppGame::Draw3D::cube(4, -2, 0, 100, 1, 100, 200, 200, 200);
        background.bind();
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                CppGame::Draw3D::cube(i * 2 + 5, 0, j * 2, 1, 1, 1, 200 * ((i + j) % 2), 200 * ((i + j) % 2), 200 * ((i + j) % 2));
            }
        }
        CppGame::Draw3D::billboard(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 2.0f), image);
        plane.draw(*CoreGeometry::shader3d_ptr, camera, glm::vec3(0.0f, 2.0f, 0.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f));
        scroll.draw(*CoreGeometry::shader3d_ptr, camera, glm::vec3(0.0f, 2.0f, 4.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(-0.01f, -0.01f, -0.01f));
        if (glGetError() == GL_INVALID_OPERATION){
            std::cout << "this is written once btw flag 1\n";
            throw std::runtime_error("FUCK!!!!");
        }

        // swaps two image buffers.
        renderer.postdraw();
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