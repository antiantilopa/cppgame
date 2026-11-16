#pragma once

#include "cppgame.h"

#include <string>
#include <vector>

namespace CppGame {

class Engine{
public:
    Window& window;
    Camera& camera;

    explicit Engine(Renderer& renderer);
    void init(int width, int height, std::string title);
    void add_updateable(Updateable& obj);
    void remove_updateable(Updateable& obj);
    void run();
private:
    Renderer& renderer;
    std::vector<Updateable*> updateable;
};

}
