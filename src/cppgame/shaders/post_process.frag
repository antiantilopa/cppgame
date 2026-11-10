#version 330 core

in vec4 out_color;
in vec2 out_tex_coord;

uniform sampler2D texture1;

out vec4 FragColor;

const float pi = 3.14159265358979f;

void main()
{
    FragColor = out_color;
    FragColor = texture(texture1, (sin((out_tex_coord-0.5) * pi)) / 2 + 0.5) * out_color;
    // if (length(FragColor) < 1.1f){
    //     discard;
    // }
    // return;
    // FragColor = FragColor * FragColor;
    // FragColor = vec4(FragColor.r, FragColor.g, FragColor.b, 1.0);
}