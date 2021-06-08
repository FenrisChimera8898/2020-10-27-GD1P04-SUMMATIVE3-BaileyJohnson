#version 450 core

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoords;

out vec4 color;

uniform sampler2D ImageTexture;
uniform float ambientStr   = 0.05f;
uniform vec3  ambientColor = vec3(1.0f, 1.0f, 1.0f);
uniform vec3  lightColor   = vec3(1.0f, 1.0f, 1.0f);
uniform vec3  lightPos   = vec3(-2.0, 6.0f, 3.0f);


void main(void)
{
//Ambient
vec3 ambient = ambientStr * ambientColor;

//Light Direction
vec3 norm = normalize(fragNormal);
vec3 lightDir = normalize(fragPos - lightPos);

//Diffuse Coloring
float diffuseStr = max(dot(norm, -lightDir), 0.5f);
vec3 diffuse = diffuseStr * lightColor;

color = vec4(ambient + diffuse, 1.0f) * (texture(ImageTexture, fragTexCoords));
}