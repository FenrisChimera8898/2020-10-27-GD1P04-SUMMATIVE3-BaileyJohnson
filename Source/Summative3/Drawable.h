#pragma once
// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : Drawable.h
//  Description : Drawable class for Hexagon and Quad to inherit from
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
// 
// Library Includes 

// Local Includes 

// This Include 

// Variables 

// Function Prototypes 


// Implementation
#include "ShaderLoader.h"
#include "Camera.h"
#include <freeglut.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Drawable
{
public:
	Drawable() {};
	virtual ~Drawable() {};
	virtual void Render() = 0;


	GLuint Texture;
	glm::mat4 cameraMat;
	glm::vec3 vObjSize;
	glm::vec3 objPosition;

	GLfloat* Vertices;
	GLuint* Indices;

	GLuint Program;

	GLuint VAO;

	//Matrices
	glm::mat4 translationMat;

	float objRotationAngle;
	glm::mat4 rotationMat;

	glm::vec3 objScale;
	glm::mat4 scaleMat;

	glm::mat4 modelMat;

	const glm::vec3 worldRotationAxis_Z = glm::vec3(0.0f, 0.0f, 1.0f);
};

