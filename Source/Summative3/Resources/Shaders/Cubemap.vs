#version 450 core

layout (location = 0) in vec3 Position;

out vec3 FragTexCoords;

uniform mat4 PVM;

void main() 
{
	gl_Position = PVM * vec4(Position, 1.0);
	FragTexCoords = Position;
}