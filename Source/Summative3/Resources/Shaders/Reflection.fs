#version 450 core

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 color;

uniform vec3 CamPos;
uniform sampler2D ImageTexture;
uniform samplerCube skybox;

void main(void)
{
	vec3 norm = normalize(fragNormal);
	vec3 viewDir = normalize(fragPos - CamPos);
	vec3 reflectDir = reflect(viewDir, norm) * - 1;

	color = vec4(texture(skybox, reflectDir).rgb, 1.0f);
}