#version 330 core

layout (location = 0) in vec3 aPos;

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

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 out_color;
out vec3 relpos;

void main(){
    vec4 outputpos = vec4((aPos.x * width + x * 2), (aPos.y * height + y * 2), (aPos.z * depth + z * 2), 1.0);
    gl_Position = proj * view * model * outputpos;
    out_color = color;
    relpos = vec3(aPos.x * width / 2, aPos.y * height / 2, aPos.z * depth / 2);
    return;
}