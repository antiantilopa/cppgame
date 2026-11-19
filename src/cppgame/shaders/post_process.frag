#version 330 core

in vec4 out_color;
in vec2 out_tex_coord;

uniform sampler2D texture1;
uniform float width;
uniform float height;

out vec4 FragColor;

const float pi = 3.14159265358979f;

float offset_x = 1.0f / width; 
float offset_y = 1.0f / height; 

vec2 offsets[9] = vec2[](
    vec2(-offset_x, offset_y), vec2(0.0f, offset_y), vec2(offset_x, offset_y),
    vec2(-offset_x, 0.0f), vec2(0.0f), vec2(offset_x, 0.0f),
    vec2(-offset_x, -offset_y), vec2(-offset_y), vec2(offset_x, -offset_y)
);

float kernel[9] = float[](
    -1, -1, -1,
    -1, +9, -1,
    -1, -1, -1
);

void main()
{
    vec3 color = vec3(0.0f);
    for (int i = 0; i < 9; i++){
        color += texture(texture1, out_tex_coord + offsets[i]).rgb * kernel[i];
    }
    FragColor = vec4(color, 1.0f) * out_color;
    // if (length(FragColor) < 1.1f){
    //     discard;
    // }
    // return;
    // FragColor = FragColor * FragColor;
    // FragColor = vec4(FragColor.r, FragColor.g, FragColor.b, 1.0);
}