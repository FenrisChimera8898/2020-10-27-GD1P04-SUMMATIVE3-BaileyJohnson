#pragma once
// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : GameManager.h
//  Description : GameManager class to manage a bool variable
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
// 
// Implementation
class GameManager
{
public:
	GameManager(); //Constructor
	~GameManager(); //Deconstructor

	//Bool variable that stores whether the game is being played or not. 
	//(True = Game is playing, False = Menu is running)
	static bool playing;
};