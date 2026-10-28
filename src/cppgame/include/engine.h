#pragma once

#include "cppgame.h"

#include <string>

namespace CppGame {

class Engine {
public:
    Window& window;
    Camera& camera;

    explicit Engine(Renderer& renderer);
    void init(int width, int height, std::string title);
    void run();
private:
    Renderer& renderer;
};

}
