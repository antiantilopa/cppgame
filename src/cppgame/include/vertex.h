#ifndef VERTEX_H
#define VERTEX_H

#include "glm/glm.hpp"

struct Vertex3d{
    glm::vec3 position = glm::vec3();
    glm::vec3 normal = glm::vec3();
    glm::vec3 color = glm::vec3();
    glm::vec2 texture = glm::vec2();

    static const inline unsigned char POS_SIZE = 3;
    static const inline unsigned char NORMAL_SIZE = 3;
    static const inline unsigned char COLOR_SIZE = 3;
    static const inline unsigned char TEXTURE_SIZE = 2;
    static const inline unsigned char POS = 0b000;
    static const inline unsigned char POS_NORMAL = 0b001;
    static const inline unsigned char POS_COLOR = 0b010;
    static const inline unsigned char POS_NORMAL_COLOR = 0b011;
    static const inline unsigned char POS_TEXTURE = 0b100;
    static const inline unsigned char POS_NORMAL_TEXTURE = 0b101;
    static const inline unsigned char POS_COLOR_TEXTURE = 0b110;
    static const inline unsigned char POS_NORMAL_COLOR_TEXTURE = 0b111;
    
    static const inline unsigned int offset_lookup[8] = {12, 24, 24, 36, 20, 32, 32, 44}; 
    static const inline unsigned int MAX_SIZE = 11;
};

struct Vertex2d{
    glm::vec2 position = glm::vec3();
    glm::vec4 color = glm::vec4();
    glm::vec2 texture = glm::vec2();

    static const inline unsigned char POS_SIZE = 2;
    static const inline unsigned char COLOR_SIZE = 4;
    static const inline unsigned char TEXTURE_SIZE = 2;
    static const inline unsigned char POS = 0b000;
    static const inline unsigned char POS_COLOR = 0b01;
    static const inline unsigned char POS_TEXTURE = 0b10;
    static const inline unsigned char POS_COLOR_TEXTURE = 0b11;

    static const inline unsigned int offset_lookup[4] = {8, 24, 16, 32}; 
    static const inline unsigned int MAX_SIZE = 8;
};

#endif