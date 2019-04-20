#version 330 core
out vec4 FragColor;
uniform float timedColor;

in vec4 posv4;

void main()
{
   FragColor = vec4( timedColor ) - posv4;
}