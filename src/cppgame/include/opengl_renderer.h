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
    Shader* post_process;
    
    Window& init(int width, int height, std::string title) override;
    Texture& init_screen() override;
    void setPostProcessingShader(Shader* post_process);
    void preupdate() override;
    void postupdate() override;
    void predraw() override;
    void postdraw() override;
};

}
