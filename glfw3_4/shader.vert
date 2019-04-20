#version 330 core


layout (location = 0) in vec3 aPos;

out vec4 posv4;

void main()
{
	posv4 = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}