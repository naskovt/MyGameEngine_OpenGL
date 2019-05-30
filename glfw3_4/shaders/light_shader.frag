#version 330 core
out vec4 FragColor;

uniform float l_Color;


void main()
{
	FragColor = vec4(l_Color);
	FragColor.a = 1;
}