#pragma once
// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : CubeMap_SkyBox.h
//  Description : CubeMap class to create and render the skybox
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
// 
// Library Includes 

#include <vector>
#include <stb_image.h>

// Local Includes 

#include "Drawable.h"

// Implementation

class CubeMap_Skybox : public Drawable
{
public:
    CubeMap_Skybox(std::vector<std::string> textures); //Constructor
    ~CubeMap_Skybox(); //Deconstructor

    void Render();
    void Update(Camera camera);

	unsigned int textureID;
	glm::mat4 PVM;
};