#include "include/engine.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <algorithm>
#include <chrono>

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
        for (Updateable* update : updateable) {
            update->preupdate();
        }

        for (Updateable* update : updateable) {
            update->update();
        }

        for (Updateable* update : updateable) {
            update->postupdate();
        }
    }
    glfwTerminate();
}

void Engine::add_updateable(Updateable& obj) {
    updateable.push_back(&obj);
}

void Engine::remove_updateable(Updateable& obj) {
    updateable.erase(std::remove(updateable.begin(), updateable.end(), &obj), updateable.end());
}

}
