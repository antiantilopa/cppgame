#pragma once

#include "cppgame.h"

#include <string>

namespace CppGame {

class OpenGLRenderer : Renderer{
public:
    ~OpenGLRenderer() override = default;
    OpenGLRenderer(int width, int height, std::string title = std::string(""));

    Window& window;
    Texture& screen;
    
    Window& init(int width, int height, std::string title) override;
    Texture& init_screen() override;
    void preupdate() override;
    void postupdate() override;
    void predraw() override;
    void postdraw() override;
};

}
