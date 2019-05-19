#version 330 core
out vec4 FragColor;

//uniform float timer;
//uniform vec4 color;
in vec2 TexCoords;
in vec4 posv4;

uniform sampler2D texture_diffuse1;


void main()
{
   FragColor = texture(texture_diffuse1, TexCoords);
}