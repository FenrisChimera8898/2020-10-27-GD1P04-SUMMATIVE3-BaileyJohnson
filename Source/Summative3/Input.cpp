// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : Input.cpp
//  Description : Input class to take the keyboard input and translate it to the correct action
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
// 
// This Include 

#include "Input.h"

// Implementation

Input::Input()
{

}

Input::~Input()
{
	delete game;
}

//Get Keyboard Input Event information and process that into the correct action
void Input::KeyBoardInput(unsigned char key, int x, int y, bool buffer[256])
{
	//If the game is running then controls will be different than if the menu is running
	//Menu Inputs
	if (GameManager::playing != true)
	{
		if (buffer['w'] || buffer['W'])
		{
			menuSelection += 1;
			if (menuSelection > 1)
			{
				menuSelection = 0;
			}
		}
		if (buffer['s'] || buffer['S'])
		{
			menuSelection -= 1;
			if (menuSelection < 0)
			{
				menuSelection = 1;
			}
		}
		if (buffer[27])
		{
			exit(0);
		}
		if (buffer[32])
		{
			//Play
			if (menuSelection == 1)
			{
				game = new Game();
				GameManager::playing = true;		
			}
			//Quit
			if (menuSelection == 0)
			{
				exit(0);
			}
		}
	}
	//Game Inputs
	else
	{
		//Player Movement
		if (buffer[key] != buffer[27])
		{
			float playerSpeed = 6.0f;
			glm::vec2 playerPos = glm::vec2(0.0f, 0.0f);
			if (buffer['w'] || buffer['W'])
			{
				playerPos.x -= playerSpeed * inDelta;
			}
			if (buffer['s'] || buffer['S'])
			{
				playerPos.x += playerSpeed * inDelta;
			}
			if (buffer['a'] || buffer['A'])
			{
				playerPos.y += playerSpeed * inDelta;
			}
			if (buffer['d'] || buffer['D'])
			{
				playerPos.y -= playerSpeed * inDelta;
			}

			game->MovePlayer(playerPos);

		}
		//Return to menu
		if (buffer[27])
		{
			GameManager::playing = false;
			delete game;
		}
	}
}

//Get Special Keyboard Input Event Information and process that into the correct action
void Input::SpecialKeyboardInput(int key, int x, int y)
{
	//If Game is running - shoot bullets
	if (GameManager::playing == true)
	{
		float bulletSpeed = 5.0f;
		glm::vec2 bulletPos = glm::vec2(0.0f, 0.0f);
		if (key == GLUT_KEY_UP)
		{
			bulletPos.x -= bulletSpeed * inDelta;
		}
		if (key == GLUT_KEY_DOWN)
		{
			bulletPos.x += bulletSpeed * inDelta;
		}
		if (key == GLUT_KEY_LEFT)
		{
			bulletPos.y += bulletSpeed * inDelta;
		}
		if (key == GLUT_KEY_RIGHT)
		{
			bulletPos.y -= bulletSpeed * inDelta;
		}
		game->SpawnBullets(bulletPos);
	}
}
