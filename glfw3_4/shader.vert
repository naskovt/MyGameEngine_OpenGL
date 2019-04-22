#version 330 core


layout (location = 0) in vec3 aPos;

out vec4 posv4;

uniform mat4 transform;

void main()
{
   gl_Position =  vec4(aPos, 1.0f);
//   gl_Position =  vec4(aPos, 1.0f) * transform;
}