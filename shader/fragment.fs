#version 330 core
out vec4 FragCorlor;

in vec2 st;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    //FragCorlor =  mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2);
    FragCorlor = texture(texture1, st);
    //FragCorlor = vec4(0.1529, 0.7412, 0.7412, 1.0);
}