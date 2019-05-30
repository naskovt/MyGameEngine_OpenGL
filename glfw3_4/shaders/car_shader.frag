#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
  
//uniform vec3 viewPos;
//uniform vec3 lightPos; 
uniform vec3 lightColor; 
uniform float ambientIntensity; 

vec3 viewPos = vec3(1.0);
vec3 lightPos = vec3(1.0); 
//vec3 lightColor = vec3(0.7); 

vec3 objectColor = vec3(0.7);


void main()
{
    // add ambient lightning, that simulates the scattering of the global light on the surroundings
    vec3 ambient = ambientIntensity * lightColor;
  	
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        

    vec3 result = (ambient + diffuse + specular) * objectColor;
    //FragColor = vec4(result, 1.0);

    FragColor = vec4(0.5,0.5,0.5, 1.0);
    FragColor.a = 0.5;
}