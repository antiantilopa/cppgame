#version 330 core

in vec3 out_color;
in vec3 relpos;

uniform float border_width;
uniform float width;
uniform float height;
uniform float depth;
uniform int shape_type; // 0 for cube, 1 for line, 2 for plane

out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    return;

    if (shape_type == 1 || shape_type == 2){
        FragColor = vec4(out_color.r, out_color.g, out_color.b, 1.0);
        return;
    }
    if (border_width < 0.0f){
        FragColor = vec4(out_color.r, out_color.g, out_color.b, 1.0);
        return;
    }
    if (abs(width - 2 * border_width) > abs(relpos.x * 2) && abs(height - 2 * border_width) > abs(relpos.y * 2) && abs(depth - 2 * border_width) > abs(relpos.z * 2)){
        FragColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
        return;
    }
}