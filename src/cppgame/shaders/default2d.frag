#version 330 core

in vec4 out_color;
in vec2 out_tex_coord;

uniform float border_width;
uniform float width;
uniform float height;
uniform int shape_type; // 0 for rect, 1 for line, 2 for texture
uniform sampler2D texture1;

out vec4 FragColor;

void main()
{
   FragColor = out_color;
   if (shape_type == 1){
      return;
   }
   if (shape_type == 2){
      FragColor = texture(texture1, out_tex_coord) * out_color;
      return;
   }
   if (border_width < 0.0f){
      return;
   }
   if (width - 2 * border_width > abs(out_tex_coord.x * 2 - 1) * width && height - 2 * border_width > abs(out_tex_coord.y * 2 - 1) * height){
      FragColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
      return;
   }
   FragColor = vec4(out_color.r, out_color.g, out_color.b, 1.0);
}