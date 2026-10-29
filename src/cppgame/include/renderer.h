#pragma once

#include "cppgame.h"

#include <string>

namespace CppGame {

class Renderer{
public:
    virtual Window init(int width, int height, std::string title);
    virtual void preupdate()=0; // TODO find a way to not do "=0", but make it compile with g++
    virtual void postupdate()=0;
    virtual void predraw()=0;
    virtual void postdraw()=0;
};

}