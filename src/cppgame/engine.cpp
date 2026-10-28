#include "include/engine.h"
#include "GLFW/glfw3.h"
#include <iostream>

namespace CppGame {

void Engine::init(int width, int height, std::string title) {
    window = renderer.init(width, height, title);

    camera = Camera();
    camera.const_up = false;
    camera.setPosition(glm::vec3(0.0f, -0.5f, -2.0f));
    
    Mode::setOrigin(Mode::ORIGIN_CENTER);
    Mode::setDirection(Mode::DIRECTION_DOWN_RIGHT);
}

void Engine::run() {
    auto last_time = std::chrono::steady_clock::now();
    while (!window.exitPressed()) {
        // update
    }
    glfwTerminate();
}

}
