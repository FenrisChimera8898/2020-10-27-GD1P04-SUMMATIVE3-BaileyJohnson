#pragma once
// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : Bullets.h
//  Description : Bullets class that is a child of Cube class to create Bullet objects as Cube objects
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
// 
// This Include

#include "Cube.h"

// Implementation

class Bullets : public Cube
{
public:
	//Constructor - Passed to the Cube Constructor
	Bullets(GLuint texture, glm::mat4 camMat, glm::vec3 size, glm::vec3 position, bool visible, std::string vsPath, std::string fsPath, CubeMap_Skybox* sky, Camera* camera) : Cube(texture, camMat, size, position, visible, vsPath, fsPath, sky, camera) {}

	//Stored Movement
	glm::vec2 storedDirection;
};