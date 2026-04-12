#version 330 core

in vec3 out_color;
in vec3 relpos;

out vec4 FragColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    vec4 clr = model * view * proj * vec4(relpos, 1.0f);
    FragColor = vec4(vec3(clr) * out_color, 0.5f);
    return;
}