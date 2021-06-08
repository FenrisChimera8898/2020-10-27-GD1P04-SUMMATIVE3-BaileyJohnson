#version 450 core

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoords;

out vec4 color;

uniform sampler2D ImageTexture;
uniform float ambientStr   = 0.15f;
uniform vec3  ambientColor = vec3(1.0f, 1.0f, 1.0f);
uniform vec3  lightColor   = vec3(1.0f, 1.0f, 1.0f);
uniform vec3  lightPos   = vec3(50.0f, 50.0f, 50.0f);

uniform vec3 CamPos;
uniform float lightSpecStr = 0.2f;
uniform float shininess    = 32.0f;

uniform float rimExponent = 1.0f;
uniform vec3 rimColor   = vec3(1.0f, 0.0f, 0.0f);

void main(void)
{
//Ambient
vec3 ambient = ambientStr * ambientColor;

//Light Direction
vec3 norm = normalize(fragNormal);
vec3 lightDir = normalize(fragPos - lightPos);

//Diffuse Coloring
float diffuseStr = max(dot(norm, -lightDir), 0.0f);
vec3 diffuse = diffuseStr * lightColor;

//Specular highlight
vec3 negViewDir = normalize(CamPos - fragPos);
vec3 halfwayVec = normalize(-lightDir + negViewDir);
float spec = pow(max(dot(norm, halfwayVec), 1.0f), shininess);
vec3 specular = lightSpecStr * spec * lightColor;

//rim lighting
float rimFactor = 1.0f - dot(norm, negViewDir); //rim factor
rimFactor = smoothstep(0.0f, 1.0f, rimFactor);   //constrain it to the range 0-1
rimFactor = pow(rimFactor, rimExponent);       //raise it to the rim exponent
vec3 rim = rimFactor * rimColor * lightColor; //calculate the final rim component

color = vec4(ambient + diffuse + specular + rim, 1.0f) * (texture(ImageTexture, fragTexCoords));
}