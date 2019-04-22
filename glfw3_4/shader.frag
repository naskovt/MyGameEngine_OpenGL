#version 330 core
out vec4 FragColor;

uniform float timedColor;

in vec4 posv4;

void main()
{
   FragColor = vec4( vec4(0,1,0,1) * timedColor ) - posv4;
}