#pragma once

#include "cppgame.h"

#include <string>

namespace CppGame {

class Renderer{
public:
    virtual ~Renderer() = default;
    virtual Window& init(int width, int height, std::string title) = 0;
    virtual Texture& init_screen() = 0;
    virtual void preupdate() = 0;
    virtual void postupdate() = 0;
    virtual void predraw() = 0;
    virtual void postdraw() = 0;
};

}