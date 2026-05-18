#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 cam_matrix;
uniform vec3 cam_pos;
uniform vec2 size;
uniform mat4 modelab;

out vec2 tex_coord;

void main() {
    vec4 size_v4 = vec4(size, 0.0f, 1.0f);
    vec3 delme = cam_pos;
    mat4 cam_model_mat = cam_matrix * modelab;
    gl_Position = cam_model_mat * vec4(-0.5f, 0.0f, 0.0f, 1.0f); 
    tex_coord = vec2(1.0f, 0.0f);
    EmitVertex();
    gl_Position = cam_model_mat * vec4(0.5f, 0.0f, 0.0f, 1.0f); 
    tex_coord = vec2(0.0f, 0.0f);
    EmitVertex();
    gl_Position = cam_model_mat * vec4(-0.5f, 1.0f, 0.0f, 1.0f); 
    tex_coord = vec2(1.0f, 1.0f);
    EmitVertex();
    gl_Position = cam_model_mat * vec4(0.5f, 1.0f, 0.0f, 1.0f); 
    tex_coord = vec2(0.0f, 1.0f);
    EmitVertex();
    EndPrimitive();
} 