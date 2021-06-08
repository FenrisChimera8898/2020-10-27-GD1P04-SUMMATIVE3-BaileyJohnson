#pragma once
// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : Camera.h
//  Description : Camera class to create a camera from given parameters
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
// 
// Library Includes 

// Local Includes 

// This Include 

// Variables 

// Function Prototypes 


// Implementation
#include <freeglut.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Camera
{
public:
	Camera();
	~Camera();
	void Update(float delta);
	glm::mat4 GetCameraMat();

	glm::vec3 cameraPos;
protected:
	glm::vec3 cameraUpDir;
	glm::mat4 viewMat;
	glm::mat4 projectionMat;
	float timeElapsed;
	glm::mat4 PVM;

	const unsigned int screenWidth = 900;
	const unsigned int screenHeight = 900;
};

