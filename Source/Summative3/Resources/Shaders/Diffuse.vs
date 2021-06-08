#version 450 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoords;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexCoords;

uniform mat4 CamMat;
uniform mat4 ModelMat;

void main(void)
{
	gl_Position = CamMat * ModelMat * vec4(Position, 1.0f);
	fragPos = vec3(ModelMat * vec4(Position, 1.0f));
	fragNormal = mat3(transpose(inverse(ModelMat))) * Normal;
	fragTexCoords = TexCoords;
}