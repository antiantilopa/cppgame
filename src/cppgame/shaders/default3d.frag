#version 330 core

in vec3 out_color;
in vec3 relpos;

out vec4 FragColor;

uniform mat4 model;

void main()
{
    vec4 clr = model * vec4(relpos, 1.0f);
    FragColor = vec4(vec3(clr), 1.0f);
    return;
}