// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : Player.cpp
//  Description : Player Class to create, render, and update the player pyramid object
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
// 
// This Include 

#include "Player.h"

// Implementation

//Constructor
Player::Player(GLuint texture, glm::mat4 camMat, glm::vec3 size, glm::vec3 position)
{
	Texture = texture;
	cameraMat = camMat;
	vObjSize = size;
	objPosition = position;

	//Pyramid
	GLfloat Vertices_Pyr[] = {
		//Position				Normal				Texture
		-1.0f,  -1.0f,  -1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, //0
		-1.0f,  -1.0f, 1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, //1
		 1.0f,  -1.0f, 1.0f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f, //2
		 1.0f,  -1.0f,  -1.0f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, //3

		 //Side 1
		-1.0f,  -1.0f,  -1.0f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, //4
		 1.0f,  -1.0f,  -1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, //5

		//Side 2
		 1.0f,  -1.0f,  -1.0f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, //6
		 1.0f,  -1.0f,  1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, //7

		//Side 3
		 1.0f,  -1.0f,  1.0f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, //8
		-1.0f,  -1.0f, 1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, //9

		//Side 4
		-1.0f,  -1.0f, 1.0f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, //10
		-1.0f,  -1.0f,  -1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, //11

		//Top
		 0.0f,  1.0f,  0.0f,	0.0f, 0.0f, 1.0f,	0.5f, 0.0f, //12
	};

	GLuint Indices_Pyr[] = {

		1, 0, 3, //Bottom Tri 1
		1, 3, 2, //Bottom Tri 2

		4, 12, 5,	//Side 1
		6, 12, 7,	//Side 2
		8, 12, 9,	//Side 3
		10, 12, 11, //Side 4
	};

	Vertices = new GLfloat[sizeof(Vertices_Pyr) / sizeof(GLfloat)];
	for (int i = 0; i < sizeof(Vertices_Pyr) / sizeof(GLfloat); i++)
	{
		Vertices[i] = Vertices_Pyr[i];
	}

	Indices = new GLuint[sizeof(Indices_Pyr) / sizeof(GLuint)];
	for (int i = 0; i < sizeof(Indices_Pyr) / sizeof(GLuint); i++)
	{
		Indices[i] = Indices_Pyr[i];
	}

	//Create Program
	Program = ShaderLoader::CreateProgram("Resources/Shaders/Diffuse.vs", "Resources/Shaders/RimLighting.fs");

	VAO = ShaderLoader::CreateShape(sizeof(Indices_Pyr), Indices, sizeof(Vertices_Pyr), Vertices);
}

//Deconstructor
Player::~Player()
{

}

void Player::Render()
{
	// All rendering code here
	glUseProgram(Program);

	GLuint CamLoc = glGetUniformLocation(Program, "CamMat"); //Camera Mat
	glUniformMatrix4fv(CamLoc, 1, GL_FALSE, glm::value_ptr(cameraMat));

	GLuint ModelLoc = glGetUniformLocation(Program, "ModelMat"); //Model Mat
	glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glUniform1i(glGetUniformLocation(Program, "ImageTexture"), 0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}

void Player::Update(float delta)
{
	glm::vec3 transPos = glm::vec3(objPosition.x - (vObjSize.x / 2), objPosition.y, objPosition.z - (vObjSize.z / 2));
	translationMat = glm::translate(glm::mat4(), transPos);

	objRotationAngle = 0.0f;
	rotationMat = glm::rotate(glm::mat4(), glm::radians(objRotationAngle), worldRotationAxis_Z);

	scaleMat = glm::scale(glm::mat4(), vObjSize);

	modelMat = translationMat * rotationMat * scaleMat;

	glutPostRedisplay();
}