#pragma once

#include "cppgame.h"

#include <string>

namespace CppGame {

class Renderer {
public:
    virtual Window init(int width, int height, std::string title);
    virtual void preupdate();
    virtual void postupdate();
    virtual void predraw();
    virtual void postdraw();
};

}