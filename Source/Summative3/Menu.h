#pragma once
// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : Menu.h
//  Description : Menu class to render menu texts and change colour from Input menu selection variable
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
// 
// Local Includes 

#include "Text.h"

// Implementation

class Menu
{
public:
	Menu(); //Constructor - creates all objects for the menu
	~Menu(); //Deconstructor

	//Menu Render Function - Takes in variabel to change render colours based on selected option
	void Render(int menuSelection);

	//Text Objects
	Text* Title;
	Text* Play;
	Text* Quit;

	Text* gameOver;
	Text* gameOver2;

	Text* menuControls;

	Text* Goal;

	Text* gameControls1;
	Text* gameControls2;
	Text* gameControls3;

	//Int variables to store values from last game played
	static int intScoreMenu;
	static int intWaveMenu;

	//Bool variable to store if a game has been played yet - (True - display last game stats, False = nothing)
	static bool gamePlayed;
};