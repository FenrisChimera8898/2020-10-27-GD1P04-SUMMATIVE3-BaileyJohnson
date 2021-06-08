#pragma once
// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : Input.h
//  Description : Input class to take the keyboard input and translate it to the correct action
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
// 
// Library Includes 

#include <iostream>

// Local Includes 

#include "Menu.h"
#include "Game.h"
#include "GameManager.h"

// Implementation

class Input
{
public:
	Input(); //Constructor
	~Input(); //Deconstructor

	//Get Keyboard Input Event information and process that into the correct action
	void KeyBoardInput(unsigned char key, int x, int y, bool buffer[256]);

	//Get Special Keyboard Input Event Information and process that into the correct action
	void SpecialKeyboardInput(int key, int x, int y);

	//Int to manage what menu option is selected
	int menuSelection = 1;

	//GameManager object to store bool variable
	GameManager manager;

	//Actual Game object
	Game* game;

	//Delta Time Given from main.cpp
	float inDelta;
};