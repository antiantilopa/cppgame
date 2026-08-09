#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 2) in vec2 aTexture;

uniform float window_width;
uniform float window_height;

out vec2 tex_coord;

void main(){
    tex_coord = aTexture;
    gl_Position = vec4((2 * aPos / vec2(window_width, -window_height)) - vec2(1.0f, -1.0f), 0.0f, 1.0f);
    return;
}