#pragma once
// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : Cube.h
//  Description : Cube class to create,render, and update cube objects (Enemies, BUllets)
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
// 
// This Include

#include "Drawable.h"
#include "CubeMap_Skybox.h"

// Implementation

class Cube : public Drawable
{
public:
	//Constructor
	Cube(GLuint texture, glm::mat4 camMat, glm::vec3 size, glm::vec3 position, bool visible, std::string vsPath, std::string fsPath, CubeMap_Skybox* sky, Camera* camera);
	~Cube(); //Deconstructor

	void Render();
	void Update(float delta);

	bool visible;
	glm::vec3 cameraPos;

	CubeMap_Skybox* skybox;
};

