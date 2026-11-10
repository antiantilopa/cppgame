#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexture;

uniform vec3 color;

out vec4 out_color;
out vec2 out_tex_coord;

void main(){
    out_color = vec4(color, 1.0);
    out_tex_coord = aTexture;
    vec4 outputpos = vec4(aPos.x, aPos.y, 0.0, 1.0);
    gl_Position = outputpos;
    return;
}