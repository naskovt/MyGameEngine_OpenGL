#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

vec4 grey = vec4(0.1,0.1,0.1,1);

void main()
{
   FragColor = grey;
}