// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : CubeMap_SkyBox.cpp
//  Description : CubeMap class to create and render the skybox
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
// 
// This Include

#include "CubeMap_Skybox.h"

// Implementation

//Constructor
CubeMap_Skybox::CubeMap_Skybox(std::vector<std::string> textures)
{
	GLfloat Vertices_Cube[] = {
		//Position				Normal				Texture
		// front
			-1.0, -1.0,  1.0,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
			 1.0, -1.0,  1.0,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f,
			 1.0,  1.0,  1.0,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
			-1.0,  1.0,  1.0,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
		// back
			-1.0, -1.0, -1.0,	0.0f, 0.0f, 1.0f,	0.5f, 0.5f,
			 1.0, -1.0, -1.0,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
			 1.0,  1.0, -1.0,	0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
			-1.0,  1.0, -1.0,	0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
	};
	GLuint Indices_Cube[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3,
	};
	
	Vertices = new GLfloat[sizeof(Vertices_Cube) / sizeof(GLfloat)];
	for (int i = 0; i < sizeof(Vertices_Cube) / sizeof(GLfloat); i++)
	{
		Vertices[i] = Vertices_Cube[i];
	}

	Indices = new GLuint[sizeof(Indices_Cube) / sizeof(GLuint)];
	for (int i = 0; i < sizeof(Indices_Cube) / sizeof(GLuint); i++)
	{
		Indices[i] = Indices_Cube[i];
	}
	
	//Create program
	Program = ShaderLoader::CreateProgram("Resources/Shaders/Cubemap.vs", "Resources/Shaders/Cubemap.fs");
	
	//Create and assign VAO/VBO/EBO DATA
	VAO = ShaderLoader::CreateShape(sizeof(Indices_Cube), Indices, sizeof(Vertices_Cube), Vertices);
	
	//Generate a single Texture ID
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	GL_TEXTURE_CUBE_MAP_POSITIVE_X; //RIGHT
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X; //LEFT
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y; //TOP
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y; //BOTTOM
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z; //BACK
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; //FRONT
	
	int width, height;
	unsigned char* image;
	for (GLuint i = 0; i < 6; i++) {
		std::string fullPathName = "Resources/Textures/CubeMap/";
		fullPathName.append(textures[i]);
		image = stbi_load(fullPathName.c_str(),
			&width,
			&height,
			0,
			STBI_rgb_alpha);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0,
			GL_RGBA,
			width,
			height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			image);
		stbi_image_free(image);
	}
	
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

//Deconstructor
CubeMap_Skybox::~CubeMap_Skybox()
{

}

void CubeMap_Skybox::Render()
{
	glUseProgram(Program);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glUniform1i(glGetUniformLocation(Program, "cubeSampler"), 0);
	glUniformMatrix4fv(glGetUniformLocation(Program, "PVM"), 1, GL_FALSE, glm::value_ptr(PVM));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void CubeMap_Skybox::Update(Camera camera)
{
	glm::mat4 model = glm::scale(glm::mat4(), glm::vec3(2000.0f, 2000.0f, 2000.0f));
	PVM = camera.GetCameraMat() * model;
}