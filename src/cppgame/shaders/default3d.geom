#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT{
    vec3 out_color;
    vec3 relpos;
    vec3 normal;
    vec3 current_pos;
} gs_in[];


out vec3 out_color;
out vec3 relpos;
out vec3 normal;
out vec3 current_pos;
out vec2 tex_coord;

vec3 GetNormal(){
    vec3 a = vec3(gs_in[0].current_pos) - vec3(gs_in[1].current_pos);
    vec3 b = vec3(gs_in[2].current_pos) - vec3(gs_in[1].current_pos);
    return normalize(cross(a, b));
}
vec2 GetTex(int i){
    float y;
    float x;
    if (gs_in[i % 3].relpos.y == gs_in[(i + 1) % 3].relpos.y && gs_in[i % 3].relpos.y == gs_in[(i + 1) % 3].relpos.y){
        y = (gs_in[i % 3].relpos.x + 1.0f) / 2.0f;
        x = abs(gs_in[i % 3].relpos.y - gs_in[i % 3].relpos.z) / 2.0f;
        return vec2(x, y);
    }
    y = (gs_in[i % 3].relpos.y + 1.0f) / 2.0f;
    x = abs(gs_in[i % 3].relpos.x - gs_in[i % 3].relpos.z) / 2.0f;
    return vec2(x, y);
}
void main(){
    out_color = gs_in[0].out_color;
    relpos = gs_in[0].relpos;
    normal = GetNormal();
    current_pos = gs_in[0].current_pos;
    tex_coord = GetTex(0);
    gl_Position = gl_in[0].gl_Position; 
    EmitVertex();
    out_color = gs_in[1].out_color;
    relpos = gs_in[1].relpos;
    normal = GetNormal();
    current_pos = gs_in[1].current_pos;
    tex_coord = GetTex(1);
    gl_Position = gl_in[1].gl_Position; 
    EmitVertex();
    out_color = gs_in[2].out_color;
    relpos = gs_in[2].relpos;
    normal = GetNormal();
    current_pos = gs_in[2].current_pos;
    tex_coord = GetTex(2);
    gl_Position = gl_in[2].gl_Position; 
    EmitVertex();
    EndPrimitive();
} 