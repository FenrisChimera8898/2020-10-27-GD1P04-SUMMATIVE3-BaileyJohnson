#pragma once
// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : Player.h
//  Description : Player Class to create, render, and update the player pyramid object
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
// 
// Local Includes 

#include "Drawable.h"

// Implementation

class Player : public Drawable
{
public:
	//Constructor
	Player(GLuint texture, glm::mat4 camMat, glm::vec3 size, glm::vec3 position);
	~Player(); //Deconstructor

	void Render();
	void Update(float delta);
};