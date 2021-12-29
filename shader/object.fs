#version 330 core

#define NR_POINT_LIGHTS 2

struct Material{
    vec3 ka;
    vec3 kd;
    vec3 ks;
    float shininess;
    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;
    sampler2D texture_diffuse3;
    sampler2D texture_specular1;
    sampler2D texture_specular2;
};

struct PointLight{
    vec3 lightColor;
    vec3 lightPos;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 st;

out vec4 FragColor;

uniform vec3 eyePos;
uniform vec3 intensityAmbient;
uniform Material M;
uniform PointLight Light[NR_POINT_LIGHTS];

vec3 CalcPointLight(PointLight L)
{
    vec3 ambient = M.ka * intensityAmbient;

    float lightDistance = distance(L.lightPos, FragPos);
    vec3 lightDir = normalize(L.lightPos - FragPos);
    float cosIn = dot(normalize(Normal), lightDir);
    vec3 diffuse = M.kd * vec3(texture(M.texture_diffuse1, st).xyz) * (L.lightColor) * max(cosIn, 0);

    vec3 viewDir = normalize(eyePos - FragPos);
    vec3 halfVec = normalize(lightDir + viewDir);
    vec3 specular = vec3(texture(M.texture_specular1, st).xyz) * (L.lightColor / pow(lightDistance, 2)) * pow(max(dot(halfVec, normalize(Normal)), 0), M.shininess);
    //vec3 specular = M.ks * (L.lightColor / pow(lightDistance, 2)) * pow(max(dot(halfVec, normalize(Normal)), 0), M.shininess);

    return (ambient + diffuse + specular);
}

void main()
{
    vec3 finalColor = vec3(0.0, 0.0, 0.0); 
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
    {
        finalColor += CalcPointLight(Light[i]);
    }
    
    //FragColor = texture(M.texture_diffuse1, st);
    FragColor = vec4(finalColor, 1.0f);    
    //FragColor = vec4(CalcPointLight(Light[0]), 1.0);
}