#pragma once
// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : Plane.h
//  Description : Plane class to create a Plane object from the given parameters. (acting as player in this project)
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
//
// Local Includes 

#include "Drawable.h"
#include "CubeMap_Skybox.h"

// Implementation

class Plane : public Drawable
{
public:
	//Constructor
	Plane(GLuint texture, glm::mat4 camMat, glm::vec3 size, glm::vec3 position, CubeMap_Skybox* sky, Camera* camera);
	~Plane(); //Deconstructor

	void Render();
	void Update(float delta);

	CubeMap_Skybox* skybox;
	glm::vec3 cameraPos;
};

