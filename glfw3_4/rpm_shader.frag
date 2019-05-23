#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform float timer;

void main()
{
   FragColor =  vec4(1-TexCoords.y, TexCoords.y, 0, TexCoords.y - timer);
}