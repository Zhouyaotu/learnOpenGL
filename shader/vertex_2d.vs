#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCrood;

out vec3 FragPos;
out vec3 Normal;
out vec2 st;

uniform mat4 m;
uniform mat4 v;
uniform mat4 p;

void main()
{
    gl_Position =  p * v * m * vec4(aPos.x, aPos.y, 0.0, 1.0);
    FragPos = vec3((m * vec4(aPos.x, aPos.y, 0.0, 1.0)).xyz);
    st = aTexCrood;
}