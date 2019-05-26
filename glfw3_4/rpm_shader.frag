#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D _diffuse;
uniform sampler2D _alpha;
uniform float _gasValue;

bool isVisible = false;

float GetRemainder(float num, float remainderOf){

	return  num - (remainderOf * floor(num/remainderOf));
}

void main()
{
	
	vec4 c = texture(_diffuse, 1- TexCoords);
	float _a = texture(_alpha, 1- TexCoords).a;

	FragColor = c;

	// it is 1.08 because, the gradient is not perfect
	if(c.a > 0 && _gasValue > 1.08 -_a )
	{
		FragColor.a = c.a;
	}
	else
	{
		FragColor.a = 0;
	}
}