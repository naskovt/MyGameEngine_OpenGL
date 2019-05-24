#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;


void main()
{
   FragColor = texture(texture_diffuse1, TexCoords);
   FragColor -= 0.2;
   FragColor.a = 1;

}