#version 330 core

in vec3 out_color;
in vec2 tex_coord;
in vec3 relpos;
in vec3 normal;
in vec3 current_pos;

out vec4 FragColor;

uniform vec3 albedo;
uniform float metallic;
uniform float roughness;
uniform float ao;

uniform vec4 light_color;
uniform vec3 light_pos;
uniform vec3 cam_pos;
uniform vec3 color;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

const float PI = 3.14159265359;

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

vec4 point_light() {
    vec3 norm = normalize(normal);

    vec3 light_dir = normalize(light_pos - current_pos);
    vec3 view_dir = normalize(cam_pos - current_pos);
    vec3 half_way = normalize(light_dir + view_dir);

    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

    vec3 Lo = vec3(0.0);

    vec3 L = normalize(light_pos - current_pos);
    vec3 H = normalize(view_dir + L);
    float distance = length(light_pos - current_pos);
    float attenuation = 1.0 / (distance * distance);
    vec3 radiance = light_color.xyz * attenuation;

    float NDF = DistributionGGX(norm, half_way, roughness);   
    float G   = GeometrySmith(norm, view_dir, L, roughness);      
    vec3 F    = fresnelSchlick(dot(half_way, view_dir), F0);
        
    vec3 numerator    = NDF * G * F * 10; 
    float denominator = 4.0 * max(dot(norm, view_dir), 0.0) * max(dot(norm, L), 0.0) + 0.0001;
    vec3 specular = numerator / denominator;
    
    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;	  

    float NdotL = max(dot(norm, L), 0.0); 

    Lo += (kD * albedo / PI + specular) * radiance * NdotL;
    
    vec3 ambient = vec3(0.03) * albedo * ao;

    vec3 color = ambient + Lo;

    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2)); 

    return vec4(color, 1.0);
}

void main()
{
    vec4 tex = texture2D(diffuse0, tex_coord);
    if (tex.a < 0.01){
        discard;
    }
    FragColor = point_light((tex * vec4(color, 1.0f) * light_color).xyz);
    return;
}