#pragma once

#include "cppgame.h"

#include <string>

namespace CppGame {

class OpenGLRenderer : Renderer {
public:
    Window window;
    
    Window init(int width, int height, std::string title) override;
    void preupdate() override;
    void postupdate() override;
    void predraw() override;
    void postdraw() override;
};

}
