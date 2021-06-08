#version 450 core

in vec3 N;
in vec3 v;
in vec4 ex_color;

void main()
{
	vec3 L = normalize(gl_LightSource[0].position.xyz - v);   
	vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(N,L), 0.0);  
	Idiff = clamp(Idiff, 0.0, 1.0); 
	gl_FragColor = Idiff*ex_color;
} 