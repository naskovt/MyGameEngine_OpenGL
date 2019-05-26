#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D _diffuse;


void main()
{
   FragColor = texture(_diffuse, TexCoords);

}