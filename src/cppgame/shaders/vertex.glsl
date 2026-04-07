#version 330 core

layout (location = 0) in vec2 aPos;

uniform float x;
uniform float y;
uniform float x2;
uniform float y2;
uniform float width;
uniform float height;
uniform vec3 color;
uniform float window_width;
uniform float window_height;
uniform int shape_type; // 0 for rect, 1 for line

out vec3 out_color;
out vec2 relpos;

void main(){
   if (shape_type == 0){
      vec4 outputpos = vec4((aPos.x * width + x * 2) / window_width, (aPos.y * height + y * 2) / window_height, 0.0, 1.0);
      gl_Position = outputpos;
      out_color = color;
      relpos = vec2(aPos.x * width / 2, aPos.y * height / 2);
      return;
   }else{
      vec2 line_start = vec2(x, y);
      vec2 line_end = vec2(x2, y2);
      vec2 line = line_start * (vec2(1, 1) - aPos) + line_end * (aPos + vec2(1, 1));
      vec4 outputpos = vec4(line.x / window_width, line.y / window_height, 0.0, 1.0);
      gl_Position = outputpos;
      out_color = color;
      relpos = vec2(line.x, line.y);
      return;
   }
}