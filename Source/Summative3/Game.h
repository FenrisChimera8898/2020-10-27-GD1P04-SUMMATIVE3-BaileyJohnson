#pragma once
// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : Game.h
//  Description : Game class to run gameplay
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
// 
// Library Includes 

#include <time.h>

// Local Includes 

#include "GameManager.h"
#include "Menu.h"
#include "Audio.h"
#include "CubeMap_Skybox.h"
#include "Plane.h"
#include "Player.h"
#include "Cube.h"
#include "Bullets.h"
#include "Model.h"
#include "Text.h"

// Implementation

class Game
{
public:
	Game(); //Constructor
	~Game(); //Deconstructor

	void Render();
	void Update(float delta);

	//Move Player Object based on input movement speed from Input.cpp
	void MovePlayer(glm::vec2 movement);

	//Spawn Enemies
	void SpawnEnemies(Plane& plane);
	//Move Enemies towards player
	void MoveEnemies(float delta);
	//Check if an enemy is colliding with player
	void CheckPlayerCollision();

	//Spawn Bullets moving in a direction from the player given by Input.cpp
	void SpawnBullets(glm::vec2 direction);
	//Move Bullets
	void MoveBullets();
	//Check if a bullet has collided with an enemy
	void CheckBulletCollisions();

	int intScore;
	int intPlayerLives;
	int intWaveCount;
	int intCurrEnemies;

	std::string strScore = "Score: ";
	std::string strLives = "Lives: ";
	std::string strWave = "Wave: ";
	
	Camera* camera;
	CubeMap_Skybox* skybox;

	Audio* bulletAudio;

	Text* scoreLabel;
	Text* livesLabel;
	Text* waveLabel;

	Plane* plane;

	Player* player;
	Bullets* bullets[15];

	Cube* enemies[51];

	Model* modelTank;
	Model* modelPug1;
	Model* modelPug2;
};