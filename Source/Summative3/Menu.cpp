// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : Menu.cpp
//  Description : Menu class to render menu texts and change colour from Input menu selection variable
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
// 
// This Includes 

#include "Menu.h"

// Variables 

//Int variables to store values from last game played
int Menu::intScoreMenu = 0;
int Menu::intWaveMenu = 0;

//Bool variable to store if a game has been played yet - (True - display last game stats, False = nothing)
bool Menu::gamePlayed = false;

// Implementation

//Constructor - creates all objects for the menu
Menu::Menu()
{
	Title = new Text("Menu", "Resources/Fonts/Fontin-Regular.ttf", glm::vec2(0, 100), glm::vec2(275.0f, 700.0f));
	
	Play = new Text("Play", "Resources/Fonts/Fontin-Regular.ttf", glm::vec2(0, 80), glm::vec2(325.0f, 600.0f));
	Quit = new Text("Close", "Resources/Fonts/Fontin-Regular.ttf", glm::vec2(0, 80), glm::vec2(300.0f, 500.0f));

	gameOver = new Text("Game Over!", "Resources/Fonts/Fontin-Regular.ttf", glm::vec2(0, 50), glm::vec2(270.0f, 400.0f));
	
	std::string c = "Score: " + std::to_string(intScoreMenu);
	c += "  ";
	c += "Wave: " + std::to_string(intWaveMenu);
	gameOver2 = new Text(c, "Resources/Fonts/Fontin-Regular.ttf", glm::vec2(0, 50), glm::vec2(205.0f, 325.0f));
	
	menuControls = new Text("Menu: W - Up, S - Down, Space - Select", "Resources/Fonts/Fontin-Regular.ttf", glm::vec2(0, 40), glm::vec2(50.0f, 260.0f));
	
	Goal = new Text("SURVIVE!", "Resources/Fonts/Fontin-Regular.ttf", glm::vec2(0, 50), glm::vec2(300.0f, 200.0f));
	
	gameControls1 = new Text("WASD - MOVEMENT", "Resources/Fonts/Fontin-Regular.ttf", glm::vec2(0, 40), glm::vec2(225.0f, 150.0f));
	gameControls2 = new Text("ARROW KEYS - FIRE BULLET", "Resources/Fonts/Fontin-Regular.ttf", glm::vec2(0, 40), glm::vec2(165.0f, 100.0f));
	gameControls3 = new Text("Esc - Return to Menu", "Resources/Fonts/Fontin-Regular.ttf", glm::vec2(0, 40), glm::vec2(215.0f, 50.0f));
}

//Deconstructor
Menu::~Menu()
{
	delete Title;

	delete Play;
	delete Quit;

	delete gameOver;
	delete gameOver2;

	delete menuControls;

	delete Goal;

	delete gameControls1;
	delete gameControls2;
	delete gameControls3;
}

//Menu Render Function - Takes in variabel to change render colours based on selected option
void Menu::Render(int menuSelection)
{
	Title->Render();

	if (menuSelection > 1)
	{
		menuSelection = 0;
	}
	if (menuSelection < 0)
	{
		menuSelection = 1;
	}

	//Change text colour to visualise current selection
	if (menuSelection == 1)
	{
		Play->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
		Quit->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	}
	if (menuSelection == 0)
	{
		Play->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		Quit->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
	}

	Play->Render();
	Quit->Render();

	//If a game has been played then display last game stats
	if (gamePlayed == true)
	{
		gameOver->SetColor(glm::vec3(0.0f, 1.0f, 1.0f));
		gameOver->Render();

		std::string d = "Score: " + std::to_string(intScoreMenu);
		d += "  ";
		d += "Wave: " + std::to_string(intWaveMenu);
		gameOver2->SetColor(glm::vec3(0.0f, 1.0f, 1.0f));
		gameOver2->SetText(d);
		gameOver2->Render();
	}

	menuControls->Render();

	Goal->Render();

	gameControls1->Render();
	gameControls2->Render();
	gameControls3->Render();
}