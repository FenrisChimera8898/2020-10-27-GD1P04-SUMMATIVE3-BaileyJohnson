// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : Game.cpp
//  Description : Game class to run gameplay
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
// 
// This Include 

#include "Game.h"

// Implementation

//Constructor
Game::Game()
{
	srand((unsigned int)time(NULL));

	intScore = 0;
	intPlayerLives = 10;
	intWaveCount = 0;
	intCurrEnemies = 0;
	Menu::gamePlayed = true;

	camera = new Camera();

	bulletAudio = new Audio("bulletSFX.wav");

	std::vector<std::string> skyfaces = {
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg"
	};

	skybox = new CubeMap_Skybox(skyfaces);

	glm::vec3 planSize = glm::vec3(10.0f, 0.0f, 10.0f);
	glm::vec3 planePos = glm::vec3(0.0f, 0.0f, 0.0f);
	plane = new Plane(ShaderLoader::CreateTexture("groundTexture.jpg"), camera->GetCameraMat(), planSize, planePos, skybox, camera);
	
	glm::vec3 playSize = glm::vec3(0.3f, 0.3f, 0.3f);
	glm::vec3 playPos = glm::vec3(0.0f, 0.0f + playSize.y, 0.0f);
	player = new Player(ShaderLoader::CreateTexture("playerTexture.png"), camera->GetCameraMat(), playSize, playPos);
	
	//Create all enemy objects in the array at the start of the game so that resources arent used to create them during
	glm::vec3 enemySize = glm::vec3(0.3f, 0.3f, 0.3f);
	glm::vec3 enemyPos = glm::vec3(0.0f, 0.0f + enemySize.y / 2, 0.0f);
	for (int i = 0; i < (sizeof(enemies) / sizeof(enemies[0])); i++)
	{
		enemies[i] = new Cube(ShaderLoader::CreateTexture("enemyTexture.png"), camera->GetCameraMat(), enemySize, enemyPos, false, "Resources/Shaders/Diffuse.vs", "Resources/Shaders/PhongDiffuse.fs", skybox, camera);
	}

	//Create all bullet objects in the array at the start of the game so that resources arent used to create them during
	glm::vec3 bulletSize = glm::vec3(0.1f, 0.1f, 0.1f);
	glm::vec3 bulletPos = glm::vec3(0.0f, 0.0f + playSize.y, 0.0f);
	for (int i = 0; i < (sizeof(bullets) / sizeof(bullets[0])); i++)
	{
		bullets[i] = new Bullets(ShaderLoader::CreateTexture("bulletTexture.png"), camera->GetCameraMat(), bulletSize, bulletPos, false, "Resources/Shaders/Reflection.vs", "Resources/Shaders/Reflection.fs", skybox, camera);
	}
	
	livesLabel = new Text((strLives + std::to_string(intPlayerLives)), "Resources/Fonts/Fontin-Regular.ttf", glm::vec2(0, 50), glm::vec2(30.0f, 30.0f));
	scoreLabel = new Text((strScore + std::to_string(intScore)), "Resources/Fonts/Fontin-Regular.ttf", glm::vec2(0, 50), glm::vec2(250.0f, 30.0f));
	waveLabel = new Text((strWave + std::to_string(intWaveCount)), "Resources/Fonts/Fontin-Regular.ttf", glm::vec2(0, 50), glm::vec2(500.0f, 30.0f));

	//NOTE: COULD NOT GET MODELS TO WORK AS PLAYER/ENEMIES SO LEFT THEM IN AS "DECORATION" TO SHOW I AT LEAST GOT THEM LOADING
	glm::vec3 modelTankPos = glm::vec3(-50.0f, 0.0f, 20.0f);
	modelTank = new Model("Resources/Models/Tank/Tank.obj", camera, modelTankPos);

	glm::vec3 modelPug1Pos = glm::vec3(-50.0f, 0.0f, 10.0f);
	modelPug1 = new Model("Resources/Models/pugenemy/Dog 1.obj", camera, modelPug1Pos);

	glm::vec3 modelPug2Pos = glm::vec3(-50.0f, 0.0f, 00.0f);
	modelPug2 = new Model("Resources/Models/pug/Dog 1.obj", camera, modelPug2Pos);
}

Game::~Game()
{
	Menu::intScoreMenu = intScore;
	Menu::intWaveMenu = intWaveCount;
	GameManager::playing = false;

	delete camera;
	delete skybox;
	delete plane;

	delete player;
	for (int i = 0; i < (sizeof(enemies) / sizeof(enemies[0])); i++)
	{
		delete enemies[i];
	}
	for (int i = 0; i < (sizeof(bullets) / sizeof(bullets[0])); i++)
	{
		delete bullets[i];	
	}

	delete livesLabel;
	delete scoreLabel;
	delete waveLabel;

	delete modelTank;
	delete modelPug1;
	delete modelPug2;
}

void Game::Render()
{
	skybox->Render();
	plane->Render();

	player->Render();

	scoreLabel->Render();
	livesLabel->Render();
	waveLabel->Render();

	modelTank->Render();
	modelPug1->Render();
	modelPug2->Render();

	for (int i = 0; i < (sizeof(enemies) / sizeof(enemies[0])); i++)
	{
		enemies[i]->Render();
	}
	for (int i = 0; i < (sizeof(bullets) / sizeof(bullets[0])); i++)
	{
		bullets[i]->Render();
	}
}

void Game::Update(float Delta)
{
	skybox->Update(*camera);
	camera->Update(Delta);
	plane->Update(Delta);
	player->Update(Delta);

	bulletAudio->audioSystem->update();

	for (int i = 0; i < (sizeof(enemies) / sizeof(enemies[0])); i++)
	{
		enemies[i]->Update(Delta);
	}
	for (int i = 0; i < (sizeof(bullets) / sizeof(bullets[0])); i++)
	{
		bullets[i]->Update(Delta);
	}

	if (intCurrEnemies == 0)
	{
		if (intWaveCount < 50)
		{
			intWaveCount++;
		}
		SpawnEnemies(*plane);
	}

	MoveEnemies(Delta);
	CheckPlayerCollision();
	MoveBullets();
	CheckBulletCollisions();

	if (intPlayerLives <= 0)
	{
		Menu::intScoreMenu = intScore;
		Menu::intWaveMenu = intWaveCount;
		GameManager::playing = false;
	}

	scoreLabel->SetText(strScore + std::to_string(intScore));
	livesLabel->SetText(strLives + std::to_string(intPlayerLives));
	waveLabel->SetText(strWave + std::to_string(intWaveCount));
}

//Move Player Object based on input movement speed from Input.cpp
void Game::MovePlayer(glm::vec2 movement)
{
	//Get Player and Plane bounds to create a world boundary, allowing the player to move while in the bounds but when outside the bounds it will try to push you back in
	float playerCollisionBoundXmin = player->vObjSize.x / 2 * -1 + player->objPosition.x;
	float playerCollisionBoundXmax = player->vObjSize.x / 2 + player->objPosition.x;
	float playerCollisionBoundZmin = player->vObjSize.z / 2 * -1 + player->objPosition.z;
	float playerCollisionBoundZmax = player->vObjSize.z / 2 + player->objPosition.z;

	float worldBoundXmin = plane->vObjSize.x / 2 * -1 + plane->objPosition.x;
	float worldBoundXmax = plane->vObjSize.x / 2 + plane->objPosition.x;
	float worldBoundZmin = plane->vObjSize.z / 2 * -1 + plane->objPosition.z;
	float worldBoundZmax = plane->vObjSize.z / 2 + plane->objPosition.z;

	if (playerCollisionBoundXmax < worldBoundXmax && playerCollisionBoundXmin > worldBoundXmin)
	{
		player->objPosition.x += movement.x;	
	}
	if (playerCollisionBoundXmax >= worldBoundXmax)
	{
		player->objPosition.x -= movement.x + 0.2f;
	}
	if (playerCollisionBoundXmin <= worldBoundXmin)
	{
		player->objPosition.x -= movement.x - 0.2f;
	}
	if (playerCollisionBoundZmax <= worldBoundZmax && playerCollisionBoundZmin >= worldBoundZmin)
	{
		player->objPosition.z += movement.y;
	}
	if (playerCollisionBoundZmax >= worldBoundZmax)
	{
		player->objPosition.z -= movement.y + 0.2f;
	}
	if (playerCollisionBoundZmin <= worldBoundZmin)
	{
		player->objPosition.z -= movement.y - 0.2f;
	}
}

//Spawn Enemies
void Game::SpawnEnemies(Plane& plane)
{
	//Spawn enemies within the world bounds (essentially the same as in MovePlayer but calculated differently)
	for (int i = 0; i < intWaveCount; i++)
	{
		float x = ((float)rand() / (float)(RAND_MAX) * plane.vObjSize.x) + (plane.vObjSize.x / 2) * -1 + plane.objPosition.x;
		float z = ((float)rand() / (float)(RAND_MAX) * plane.vObjSize.z) + (plane.vObjSize.z / 2) * -1 + plane.objPosition.z;

		enemies[i]->objPosition = glm::vec3(x, enemies[i]->objPosition.y, z);
		enemies[i]->visible = true;

		intCurrEnemies++;
	}   
}

//Move Enemies towards player
void Game::MoveEnemies(float delta)
{
	float maxSpeed = 1.0f * delta;
	
	for (int i = 0; i < (sizeof(enemies) / sizeof(enemies[0])); i++)
	{
		if (enemies[i]->visible)
		{
			float difX = enemies[i]->objPosition.x - player->objPosition.x;
			float difZ = enemies[i]->objPosition.z - player->objPosition.z;

			float total = abs(difX) + abs(difZ);
			float ratioX = (difX / total) * -1;
			float ratioZ = (difZ / total) * -1;

			enemies[i]->objPosition.x += maxSpeed * ratioX;
			enemies[i]->objPosition.z += maxSpeed * ratioZ;
		}
	}
}

//Check if an enemy is colliding with player
void Game::CheckPlayerCollision()
{
	//Get player and enemy bounds, if they are within each other on both the x and z axis then they are colliding
	for (int i = 0; i < (sizeof(enemies) / sizeof(enemies[0])); i++)
	{
		if (enemies[i]->visible)
		{
			bool colliX = enemies[i]->objPosition.x + enemies[i]->vObjSize.x >= player->objPosition.x + player->vObjSize.x / 2 * -1 &&
				player->objPosition.x + player->vObjSize.x / 2 >= enemies[i]->objPosition.x;
			bool colliY = enemies[i]->objPosition.z + enemies[i]->vObjSize.z >= player->objPosition.z + player->vObjSize.z / 2 * -1 &&
				player->objPosition.z + player->vObjSize.z / 2 >= enemies[i]->objPosition.z;

			if (colliX == true && colliY == true)
			{
				enemies[i]->visible = false;
				intCurrEnemies--;
				intPlayerLives--;
			}
		}
	}
}

//Spawn Bullets moving in a direction from the player given by Input.cpp
void Game::SpawnBullets(glm::vec2 direction)
{
	//The next bullet in the array that is not visible (being rendered and used) is then set to visible and used
	for (int i = 0; i < (sizeof(bullets) / sizeof(bullets[0])); i++)
	{
		if (!bullets[i]->visible)
		{
			bullets[i]->objPosition.x = player->objPosition.x - (player->vObjSize.x / 2);
			bullets[i]->objPosition.y = player->objPosition.y;
			bullets[i]->objPosition.z = player->objPosition.z - (player->vObjSize.z / 2);

			bullets[i]->storedDirection = direction;
			bullets[i]->visible = true;
			bulletAudio->audioSystem->playSound(bulletAudio->FX_Thump, 0, false, 0);
			break;
		}
	}
}

//Move Bullets
void Game::MoveBullets()
{
	//If bullet goes out of the world bounds then it is set to not visible and is then available to be used again
	for (int i = 0; i < (sizeof(bullets) / sizeof(bullets[0])); i++)
	{
		if (bullets[i]->visible)
		{
			bullets[i]->objPosition.x += bullets[i]->storedDirection.x;
			bullets[i]->objPosition.z += bullets[i]->storedDirection.y;
			
			bool colliX = bullets[i]->objPosition.x + bullets[i]->vObjSize.x >= plane->objPosition.x + plane->vObjSize.x / 2 * -1 &&
				plane->objPosition.x + plane->vObjSize.x / 2  >= bullets[i]->objPosition.x;
			bool colliY = bullets[i]->objPosition.z + bullets[i]->vObjSize.z >= plane->objPosition.z + plane->vObjSize.z / 2 * -1 &&
				plane->objPosition.z + plane->vObjSize.z / 2 >= bullets[i]->objPosition.z;

			if (colliX == false || colliY == false)
			{
				bullets[i]->visible = false;
			}
		}
	}
}

//Check if a bullet has collided with an enemy
void Game::CheckBulletCollisions()
{
	//Check bullet and enemy bounds, if they are overlapping then they are colliding
	for (int i = 0; i < (sizeof(bullets) / sizeof(bullets[0])); i++)
	{
		if (bullets[i]->visible)
		{
			for (int j = 0; j < (sizeof(enemies) / sizeof(enemies[0])); j++)
			{
				if (enemies[j]->visible)
				{
					bool colliX = bullets[i]->objPosition.x + bullets[i]->vObjSize.x >= enemies[j]->objPosition.x + enemies[j]->vObjSize.x / 2 * -1 &&
						enemies[j]->objPosition.x + enemies[j]->vObjSize.x / 2 >= bullets[i]->objPosition.x;
					bool colliY = bullets[i]->objPosition.z + bullets[i]->vObjSize.z >= enemies[j]->objPosition.z + enemies[j]->vObjSize.x / 2 * -1 &&
						enemies[j]->objPosition.z + enemies[j]->vObjSize.z / 2 >= bullets[i]->objPosition.z;

					if (colliX == true && colliY == true)
					{
						enemies[j]->visible = false;
						bullets[i]->visible = false;
						intCurrEnemies--;
						intScore++;
						break;
					}
				}
			}
		}
	}
}
