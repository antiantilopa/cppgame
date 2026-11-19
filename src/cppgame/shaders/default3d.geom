#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT{
    vec3 out_color;
    vec3 relpos;
    vec3 normal;
    vec3 current_pos;
    vec2 tex_coord;
} gs_in[];


out vec3 out_color;
out vec3 relpos;
out vec3 normal;
out vec3 current_pos;
out vec2 tex_coord;

void main(){
    // that 'if' is just even worse... TODO
    if (gs_in[0].normal == vec3(0.0f)){
        normal = cross(gs_in[0].current_pos - gs_in[1].current_pos, gs_in[0].current_pos - gs_in[2].current_pos);
        for (int i = 0; i < 3; i++){
            out_color = gs_in[i].out_color;
            relpos = gs_in[i].relpos;
            normal = normal;
            current_pos = gs_in[i].current_pos;
            tex_coord = gs_in[i].tex_coord;
            gl_Position = gl_in[i].gl_Position; 
            EmitVertex();
        }
        EndPrimitive();
    }
    else{
        for (int i = 0; i < 3; i++){
            out_color = gs_in[i].out_color;
            relpos = gs_in[i].relpos;
            normal = gs_in[i].normal;
            current_pos = gs_in[i].current_pos;
            tex_coord = gs_in[i].tex_coord;
            gl_Position = gl_in[i].gl_Position; 
            EmitVertex();
        }
        EndPrimitive();
    }
} 