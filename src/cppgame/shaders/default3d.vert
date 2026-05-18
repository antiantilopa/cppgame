#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 atexture;

uniform float x;
uniform float y;
uniform float z;
uniform float x2;
uniform float y2;
uniform float z2;
uniform float width;
uniform float height;
uniform float depth;
uniform vec3 color;
uniform float window_width;
uniform float window_height;
uniform int shape_type; // 0 for cube, 1 for line // 2 for plane

uniform mat4 cam_matrix;
uniform mat4 model;

out VS_OUT{
    vec3 out_color;
    vec3 relpos;
    vec3 normal;
    vec3 current_pos;
} vs_out;

void main(){
    vec4 outputpos = vec4((aPos.x * width + x * 2), (aPos.y * height + y * 2), (aPos.z * depth + z * 2), 1.0);
    vs_out.current_pos = vec3(model * outputpos);
    gl_Position = cam_matrix * model * outputpos;
    vs_out.out_color = color * aColor;
    vs_out.relpos = aPos;
    vs_out.normal = aNormal;
    return;
}