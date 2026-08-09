#version 330 core


uniform sampler2D font_texture;

in vec2 tex_coord;
out vec4 FragColor;

void main(){
    FragColor = texture2D(font_texture, tex_coord / vec2(16.0f));
    if (FragColor.a < 0.5f){
        discard; 
    }
    FragColor *= vec4(tex_coord / vec2(16.0f), 1.0f, 1.0f);
} 