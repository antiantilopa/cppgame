#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexture;

uniform float x;
uniform float y;
uniform float x2;
uniform float y2;
uniform float width;
uniform float height;
uniform vec3 color;
uniform float window_width;
uniform float window_height;
uniform int shape_type; // 0 for rect, 1 for line // 2 for texture

out vec4 out_color;
out vec2 out_tex_coord;

void main(){
   out_color = vec4(color, 1.0);
   out_tex_coord = aTexture;
   if (shape_type == 0 || shape_type == 2){
      vec4 outputpos = vec4((aPos.x * width + x * 2) / window_width, (aPos.y * height + y * 2) / window_height, 0.0, 1.0);
      gl_Position = outputpos;
      return;
   }
   else{
      vec2 line_start = vec2(x, y);
      vec2 line_end = vec2(x2, y2);
      vec2 line = line_start * (vec2(1, 1) - aPos) + line_end * (aPos + vec2(1, 1));
      vec4 outputpos = vec4(line.x / window_width, line.y / window_height, 0.0, 1.0);
      gl_Position = outputpos;
      return;
   }
}