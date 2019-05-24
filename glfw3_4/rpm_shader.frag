#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform float timer;
uniform float _gasValue;

bool isVisible = false;

float GetRemainder(float num, float remainderOf){

	return  num - (remainderOf * floor(num/remainderOf));
}


void main()
{
	
		// flip the UV by Y
		isVisible = 1 - TexCoords.y < _gasValue;



	FragColor =  vec4(1- TexCoords.y, TexCoords.y, 0, isVisible);
}