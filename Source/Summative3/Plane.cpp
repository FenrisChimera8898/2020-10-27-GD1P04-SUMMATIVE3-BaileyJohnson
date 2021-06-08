// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : Plane.cpp
//  Description : Plane class to create a Plane object from the given parameters. (acting as player in this project)
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
//
// Local Includes 

#include "Plane.h"

// Implementation

//Constructor
Plane::Plane(GLuint texture, glm::mat4 camMat, glm::vec3 size, glm::vec3 position, CubeMap_Skybox* sky, Camera* camera)
{
	Texture = texture;
	cameraMat = camMat;
	vObjSize = size;
	objPosition = position;
	skybox = sky;
	cameraPos = camera->cameraPos;

	//Flat plane
	GLfloat Vertices_Plane[] = {
		//Position				Colour				Texture
		0.0f, 0.0f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f, //Top - Left
		0.0f, 0.0f, 1.0f,		0.0f, 0.0f, 1.0f,	0.0f, 1.0f,	//Bot - Left
		1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f, //Bot - Right
		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f, //Top - Right
	};

	GLuint Indices_Plane[] = {
		0, 1, 2, //First Triangle
		0, 2, 3, //Second Triangle
	};

	Vertices = new GLfloat[sizeof(Vertices_Plane) / sizeof(GLfloat)];
	for (int i = 0; i < sizeof(Vertices_Plane) / sizeof(GLfloat); i++)
	{
		Vertices[i] = Vertices_Plane[i];
	}

	Indices = new GLuint[sizeof(Indices_Plane) / sizeof(GLuint)];
	for (int i = 0; i < sizeof(Indices_Plane) / sizeof(GLuint); i++)
	{
		Indices[i] = Indices_Plane[i];
	}


	//Create Program
	Program = ShaderLoader::CreateProgram("Resources/Shaders/Diffuse.vs", "Resources/Shaders/PhongDiffuse.fs");

	VAO = ShaderLoader::CreateShape(sizeof(Indices_Plane), Indices, sizeof(Vertices_Plane), Vertices);
}

//Deconstructor
Plane::~Plane()
{

}

void Plane::Render()
{
	// All rendering code here
	glUseProgram(Program);

	GLuint CamLoc = glGetUniformLocation(Program, "CamMat");
	glUniformMatrix4fv(CamLoc, 1, GL_FALSE, glm::value_ptr(cameraMat));

	GLuint ModelLoc = glGetUniformLocation(Program, "ModelMat");
	glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));

	glUniform3f(glGetUniformLocation(Program, "CamPos"), cameraPos.x, cameraPos.y, cameraPos.z);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glUniform1i(glGetUniformLocation(Program, "ImageTexture"), 0);

	glActiveTexture(GL_TEXTURE1);
	glUniform1i(glGetUniformLocation(Program, "skybox"), 1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->textureID);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}

void Plane::Update(float delta)
{
	glm::vec3 transPos = glm::vec3(objPosition.x - (vObjSize.x / 2), objPosition.y, objPosition.z - (vObjSize.z / 2));

	translationMat = glm::translate(glm::mat4(), transPos);

	objRotationAngle = 0.0f;
	rotationMat = glm::rotate(glm::mat4(), glm::radians(objRotationAngle), worldRotationAxis_Z);

	objScale = glm::vec3(vObjSize.x, 1.0f, vObjSize.z);
	scaleMat = glm::scale(glm::mat4(), objScale);

	modelMat = translationMat * rotationMat * scaleMat;

	glutPostRedisplay();
}