#version 330 core

in vec2 tex_coord;

uniform sampler2D tex;
uniform mat4 cam_matrix;
out vec4 FragColor;

void main()
{
    if (cam_matrix == mat4(0)){
        FragColor = vec4(1, 0, 0, 1);
    }
    FragColor = texture2D(tex, tex_coord);
    if (FragColor.a < 0.1f){
        discard;
    }
    return;
}