// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : Cube.cpp
//  Description : Cube class to create,render, and update cube objects (Enemies, BUllets)
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
// 
// This Include

#include "Cube.h"

// Implementation

//Constructor
Cube::Cube(GLuint texture, glm::mat4 camMat, glm::vec3 size, glm::vec3 position, bool visible, std::string vsPath, std::string fsPath, CubeMap_Skybox* sky, Camera* camera)
{
	Texture = texture;
	cameraMat = camMat;
	vObjSize = size;
	objPosition = position;
	this->visible = visible;
	skybox = sky;
	cameraPos = camera->cameraPos;

	GLfloat Vertices_Cube[] = {
		//Position				Colour				Texture
		//Front
		-0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, //0
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, //1
		 0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, //2
		 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f, //3
		
		 //Back
		-0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f, //0
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, //1
		 0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, //2
		 0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, //3

		 //Left
		-0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, //0
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, //1
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, //2
		-0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f, //3

		 //Right
		 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, //0
		 0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, //1
		 0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, //2
		 0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f, //3

		//Top
		-0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, //0
		-0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, //1
		 0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, //2
		 0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f, //3

		//Bottom
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, //0
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f, //1
		 0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, //2
		 0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f, //3
	};

	GLuint Indices_Cube[] = {

		0, 1, 2, //Front
		0, 2, 3, //Front

		7, 6, 5,
		7, 5, 4,

		8, 9, 10,
		8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		20, 21, 22,
		20, 22, 23,
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

	//Create Program
	Program = ShaderLoader::CreateProgram(vsPath.c_str(), fsPath.c_str());

	VAO = ShaderLoader::CreateShape(sizeof(Indices_Cube), Indices, sizeof(Vertices_Cube), Vertices);
}

//Deconstructor
Cube::~Cube()
{

}

void Cube::Render()
{
	if (visible)
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
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		glUseProgram(0);
	}
}

void Cube::Update(float delta)
{
	objPosition += glm::vec3(0.0f, 0.0f, 0.0f);
	translationMat = glm::translate(glm::mat4(), objPosition);

	objRotationAngle = 0.0f;
	rotationMat = glm::rotate(glm::mat4(), glm::radians(objRotationAngle), worldRotationAxis_Z);

	scaleMat = glm::scale(glm::mat4(), vObjSize);

	modelMat = translationMat * rotationMat * scaleMat;

	glutPostRedisplay();
}