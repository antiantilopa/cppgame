#include "include/RBO.h"

RBO::RBO(){
    glGenRenderbuffers(1, &ID);
}

void RBO::bind(){
    glBindRenderbuffer(GL_RENDERBUFFER, ID);
}

void RBO::unbind(){
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RBO::setStorage(int width, int height, int format){
    bind();
    glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
}

void RBO::Delete(){
    glDeleteRenderbuffers(1, &ID);
    ID = 0;
}