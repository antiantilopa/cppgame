#version 330 core

in vec3 out_color;
in vec2 tex_coord;
in vec3 relpos;
in vec3 normal;
in vec3 current_pos;

out vec4 FragColor;

uniform vec4 light_color;
uniform vec3 light_pos;
uniform vec3 color;

uniform sampler2D diffuse0;
uniform sampler2D specular0;


float base_intensity = 20.0f;
float specular_const = 0.7f;
float specular_exp = 16.0f;
float ambient_light = 0.3f;

float point_light(){
    vec3 real_cam_pos = light_pos;
    vec3 norm = normalize(normal);

    vec3 light_vec = current_pos - real_cam_pos;
    vec3 light_dir = normalize(light_vec);
    vec3 reflect_dir = reflect(-light_dir, norm);
    vec3 view_dir = normalize(current_pos - real_cam_pos);

    // intensity (inverse square)
    float dist_square = dot(light_vec, light_vec);
    float intensity = base_intensity / max(dist_square, 0.1f);
    
    // diffuse light (brightness defined by cos)
    float diffuse = max(abs(dot(norm, light_dir)), 0.0f);

    // specular light (brightness defined by reflection)
    float specular_amount = pow(max(abs(dot(reflect_dir, view_dir)), 0.0f), specular_exp);
    float specular = specular_const * specular_amount;
    float specular_tex_amount = length(texture2D(specular0, tex_coord));
    return (diffuse + specular * specular_tex_amount) * intensity + ambient_light;
}

float direct_light(){
    return 1.0f;
}

void main()
{
    vec4 tex = texture2D(diffuse0, tex_coord);
    if (tex.a < 0.01){
        discard;
    }
    // tex.xyz = vec3(tex.x + tex.y + tex.z) / 3;
    FragColor = light_color * point_light() * tex * vec4(color, 1.0f);
    return;
}