#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexture;

uniform mat4 cam_matrix;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

out VS_OUT{
    vec3 out_color;
    vec3 relpos;
    vec3 normal;
    vec3 current_pos;
    vec2 tex_coord;
} vs_out;

void main(){
    mat4 matrix = model * (-translation) * -rotation * scale;
    vs_out.current_pos = vec3(matrix * vec4(aPos, 1.0f));
    gl_Position = cam_matrix * vec4(vs_out.current_pos, 1.0);
    vs_out.out_color = aColor;
    vs_out.relpos = aPos;
    vs_out.normal = aNormal;
    vs_out.tex_coord = aTexture;
    return;
}