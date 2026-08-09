#include "include/FBO.h"

FBO::FBO(){
    glGenFramebuffers(1, &ID);
}

void FBO::bind(){
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
}
void FBO::unbind(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::bindTexture(Texture& output){
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, output.ID, 0);
    output_texture = &output;
}

void FBO::setup(){
    bind();
    glViewport(0, 0, output_texture->width, output_texture->height);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FBO::setup(Texture& output){
    bindTexture(output);
    setup();
}
