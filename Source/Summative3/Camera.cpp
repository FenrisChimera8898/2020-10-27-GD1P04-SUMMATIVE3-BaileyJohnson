// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : Camera.cpp
//  Description : Camera class to create a camera from given parameters
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
// 
// Local Includes 

#include "Camera.h"

// Implementation

Camera::Camera()
{
	cameraPos = glm::vec3(8.0f, 10.0f, 0.0f);
	cameraUpDir = glm::vec3(-1.0f, 0.0f, 0.0f);

	Update(0);
}

Camera::~Camera()
{

}

void Camera::Update(float delta)
{
	//Update Projection Mat
	float Aspect = (float)screenWidth / (float)screenHeight;
	projectionMat = glm::perspective(45.0f, Aspect, 0.01f, 10000.0f);

	timeElapsed += delta;

	viewMat = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), cameraUpDir);	
}

glm::mat4 Camera::GetCameraMat()
{
	PVM = projectionMat * viewMat;
	return PVM;
}