#include "include/mode.h"

char Mode::mode = 0x05; // default: center origin, up-right direction
char Mode::ox = 1;
char Mode::oy = 1;
char Mode::x_sign = 1;
char Mode::y_sign = 1;


void Mode::setOrigin(char origin){
    mode = (mode & 0xF0) | (origin & 0x0F);
    ox = (origin & 0x03);
    oy = (origin & 0x0C) >> 2;
}

void Mode::setDirection(char direction){
    mode = (mode & 0x0F) | (direction & 0xF0);
    if ((direction & 0x10) == 0){
        x_sign = 1;
    }
    else{
        x_sign = -1;
    }
    if ((direction & 0x20) == 0){
        y_sign = 1;
    }
    else{
        y_sign = -1;
    }
}

char Mode::getOrigin(){
    return mode & 0x0F;
}

char Mode::getDirection(){
    return mode & 0xF0;
}