#version 330 core
out vec4 FragColor;

uniform float timer;
uniform vec4 color;

in vec4 posv4;

void main()
{
   FragColor = vec4( color * timer ) - posv4;
}