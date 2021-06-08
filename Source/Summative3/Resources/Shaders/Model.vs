#version 450 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoords;

out vec2 FragTexCoords;

uniform mat4 CamMat;

void main()
{
	gl_Position = CamMat * vec4(Position, 1.0f);
	FragTexCoords = TexCoords;
}