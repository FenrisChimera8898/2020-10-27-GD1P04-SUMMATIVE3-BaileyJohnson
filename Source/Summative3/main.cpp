// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : main.cpp
//  Description : Main driver code. runs the opengl Render, Update, and Shutdown Fucntions. Also pass through keyboard input.
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
// 
// Library Includes 

#include <glew.h>
#include <freeglut.h>
#include <iostream>
#include <time.h>

// Local Includes 

#include "ShaderLoader.h"
#include "GameManager.h"
#include "Input.h"

// This Include 

// Variables 

Audio* audio;
Input* input;
Menu* menu;

float PreviousTimeStamp;
bool keyBuffer[256];

// Function Prototypes 

void Render();
void Update();
void ShutDown();
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void SpecialKeyboard(int key, int x, int y);

// Implementation

int main(int argc, char** argv)
{
	//glut and glew initialisation
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(900, 900);
	glutCreateWindow("Summative 3 - Bailey Johnson");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW initialisation has failed. Terminating application." << std::endl;
		return 0;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//Create and play background audio to run throughout the whole program
	audio = new Audio("backgroundAudio.wav");
	audio->audioSystem->playSound(audio->FX_Thump, 0, false, 0);

	//Create Input
	input = new Input();

	//Create Menu
	menu = new Menu();

	//Previous Time for DeltaTime
	PreviousTimeStamp = (float)glutGet(GLUT_ELAPSED_TIME);

	//glut Functions
	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	glutCloseFunc(ShutDown);

	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialFunc(SpecialKeyboard);

	glutMainLoop();

	return 0;
}

void Render()
{
	//All Render Code here

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//Render Game if bool is true, else Render Menu
	if (GameManager::playing == true)
	{
		input->game->Render();
	}
	else
	{
		menu->Render(input->menuSelection);
	}

	glutSwapBuffers();
}

void Update()
{
	//All Update Code here

	//Delta Time
	float CurrentTimeStamp = (float)glutGet(GLUT_ELAPSED_TIME);
	float DeltaTime = (CurrentTimeStamp - PreviousTimeStamp) * 0.001f;
	PreviousTimeStamp = CurrentTimeStamp;

	//If game is running then update game object update function
	if (GameManager::playing == true)
	{
		input->game->Update(DeltaTime);
	}
	//Pass Delta time in to Input
	input->inDelta = DeltaTime;

	//Update Audio
	audio->audioSystem->update();

	glutPostRedisplay();
}

//Shutdown - Delete objects
void ShutDown()
{
	delete audio;
	delete input;
	delete menu;
}

//Listen for keyboard down events - send information to Input
void Keyboard(unsigned char key, int x, int y)
{
	keyBuffer[key] = true;
	input->KeyBoardInput(key, x, y, keyBuffer);
}

//Listen for keyboard up events - send information to Input
void KeyboardUp(unsigned char key, int x, int y)
{
	keyBuffer[key] = false;
}

//Listen for keyboard down events of special keys - send information to Input
void SpecialKeyboard(int key, int x, int y)
{
	input->SpecialKeyboardInput(key, x, y);
}