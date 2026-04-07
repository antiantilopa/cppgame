#version 330 core

in vec3 out_color;
in vec2 relpos;

uniform float border_width;
uniform float width;
uniform float height;
uniform int shape_type; // 0 for rect, 1 for line

out vec4 FragColor;

void main()
{
   if (shape_type == 1){
      FragColor = vec4(out_color.r, out_color.g, out_color.b, 1.0);
      return;
   }
   if (border_width < 0.0f){
      FragColor = vec4(out_color.r, out_color.g, out_color.b, 1.0);
      return;
   }
   if (abs(width - 2 * border_width) > abs(relpos.x * 2) && abs(height - 2 * border_width) > abs(relpos.y * 2)){
      FragColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
      return;
   }
   FragColor = vec4(out_color.r, out_color.g, out_color.b, 1.0);
}