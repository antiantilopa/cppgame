#pragma once

#include <glad/glad.h>
#include "texture.h"

class FBO{
public:
    unsigned int ID;
    Texture* output_texture;
    FBO();
    void bind(); // do not use unknowingly !
    void unbind(); // do not use unknowingly !
    void bindTexture(Texture& output);
    // void bindRBO(); // not implemeted yet
    void setup(); //setup FBO before drawing on it
    void setup(Texture& output); //setup FBO before drawing on it
};

