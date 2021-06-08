#version 450 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec3 Color;

out vec3 fragmentNormal;
out vec4 ex_color,pos;
out vec3 N;
out vec3 v;

void main () 
{
	pos= vec4(Position,1);
	ex_color = vec4(Color,1);   
	fragmentNormal = Normal;
	
	v = vec3(gl_ModelViewMatrix * pos);       
	N = normalize(gl_NormalMatrix * Normal);
	
	gl_Position = gl_ModelViewProjectionMatrix * vec4(Position,1);
}